package geometry

import "fmt"

type Pixel struct {
	p3d *APoint
	p2d *APoint
	projected bool
	color *AColor
}

func NewPixel(p3d *APoint, color *AColor) *Pixel { p := &Pixel{p3d: p3d, color: color, projected: false}; return p; }

type Renderer struct {
	halfWidth float64
	halfHeight float64
	width, height float64
	camera *APoint
	zP []*Pixel  // Zdepth pointers
	pCache map[*APoint]*APoint
}

func NewRenderer(width, height int, camera *APoint) *Renderer {
	r := &Renderer{width: float64(width), height: float64(height)};
	r.zP = make([]*Pixel, (width + 1)*(height + 1));
	r.halfWidth = float64(width)/2;
	r.halfHeight = float64(height)/2;
	r.camera = camera;
	return r;
}

func (renderer *Renderer) project(p *Pixel) {
	if  (p.projected) {
		return;
	}
	camera := renderer.camera;
	k := camera[Z]/(p.p3d[Z] + camera[Z]);
	//fmt.Println("Rendferer::project::k::", k, "::camZ::", camera[Z], "::p3dZ::", p.p3d[Z]);
	p.p2d = &APoint{
		(renderer.halfWidth + ((p.p3d[X] - camera[X])*k + camera[X])),
		(renderer.halfHeight - ((p.p3d[Y] - camera[Y])*k + camera[Y])),
		p.p3d[Z],
	}
	//fmt.Printf("Renderter::project::[%f, %f, %f] => [%d, %d]\n", p.p3d[X], p.p3d[Y], p.p3d[Z], int(p.p2d[X]), int(p.p2d[Y]));
	p.projected = true;
}

func (renderer *Renderer) storePoint2d(aw []*Pixel) {
	for i:= 0; i < len(aw); i++ {
		if (!aw[i].projected) {
			renderer.project(aw[i]);
		}
		w := aw[i].p2d;
		if (w[X] < 0 || w[X]  > renderer.width) || (w[Y] < 0 || w[Y] > renderer.height) { continue; }
		wP :=  int(w[X] + w[Y]*renderer.width);
		zp := renderer.zP[wP];
		if zp == nil || zp.p2d[Z] <= w[Z] {
			renderer.zP[wP] = aw[i];
		}
	}
}


func (renderer *Renderer) Render(shape []*Pixel) {
	//fmt.Println("Renderer::Render::shape::len::", len(shape));
	renderer.storePoint2d(shape);
}

func (renderer *Renderer) Rotate(shape []*Pixel, rX,rY,rZ float64) []*Pixel {
	mr := NewRot([3]float64{rX, rY, rZ});
	for i:=0 ; i < len(shape); i++ {
		shape[i].p3d = mr.TransformAPoint(shape[i].p3d);
		shape[i].projected = false;
	}
	return shape;
}

func spotXY(x, y int, s string, color *AColor) {
	//fmt.Print(ESC,"[", x, ";", y, "H", s, ESC, "[38;2;", 0, 255, 0);
	var r,g,b byte;
	r=127;g=127;b=127;
	if (color != nil) {
             r = color[R]; g = color[G]; b = color[B];
	}
	fmt.Printf("%s[%d;%dH%s[48;2;%d;%d;%dm%s%s[0m", ESC, y, x, ESC, r, g, b, s, ESC);
}

const ESC = "\x1b"

func (renderer *Renderer) Draw() {
	fmt.Printf("%s[2J", ESC);
	count := 0;
	for i:= 0; i < len(renderer.zP); i++ {
		if (renderer.zP[i] != nil) {
			x := int(renderer.zP[i].p2d[X]);
			y := int(renderer.zP[i].p2d[Y]);
			spotXY(x, y, " ", renderer.zP[i].color);
			count++
			renderer.zP[i] = nil;
		}
	}
	//spotXY(0, 0, fmt.Sprintf("Drawn %d pixels", count), &AColor{255,255,10});
}

func (renderer *Renderer) Translate(shape []*Pixel, vector *AVector) []*Pixel {
	for i:=0; i < len(shape); i++ {
		shape[i].p3d = shape[i].p3d.Translate(vector);
	}
	return shape;
}

func NewShape () []*Pixel { var ap []*Pixel; return ap; }

func Append(shape []*Pixel, p3d *APoint, color *AColor) []*Pixel {
	p:=&Pixel{p3d:p3d, color:color, projected:false};
	return append(shape, p);
}

