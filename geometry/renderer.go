package geometry

import (
	"fmt"
	"math"
)

type Pixel struct {
	p3d *APoint    // The #rough 3d point coordinate
	p2d *APoint    // The "projection" of 3d point through a Renderer
	projected bool // to check if p3d was projected to avoid recomputation
	color *AColor  // RGBA color of the pixel
}

// NewPixel is the factory for a *Pixel element
// ensure that projected field is set to false
func NewPixel(p3d *APoint, color *AColor) *Pixel { p := &Pixel{p3d: p3d, color: color, projected: false}; return p; }

type Renderer struct {
	halfWidth float64      // cached computation of width/2
	halfHeight float64     // cached computation of height/2
	width, height float64  // cached cast to float64 for further computation
	camera *APoint         // Where is the camera (fixing [0,0,0] point) a simple implementation
	zP []*Pixel            // Zdepth pixels indexed by X2D%width + Y2D/width if p3d[Z] > existing pixel
}

// NewRenderer is the factory for a *Renderer
// on a pane of width,size dimension, view from a camera at camera *APoint looking to [0,0,0]
func NewRenderer(width, height int, camera *APoint) *Renderer {
	r := &Renderer{width: float64(width), height: float64(height)};
	r.zP = make([]*Pixel, (width + 1)*(height + 1));
	r.halfWidth = float64(width)/2;
	r.halfHeight = float64(height)/2;
	r.camera = camera;
	return r;
}

// project "private" method to project the 3d representation in
// the 2d pane of the renderer
func (renderer *Renderer) project(p *Pixel) {
	if  (p.projected) {
		return;
	}
	camera := renderer.camera;
	k := camera[Z]/(p.p3d[Z] + camera[Z]);
	x2d := (renderer.halfWidth + ((p.p3d[X] - camera[X])*k + camera[X]));
	y2d := (renderer.halfHeight - ((p.p3d[Y] - camera[Y])*k + camera[Y]));
	if p.p2d == nil {
		//p.p2d = &APoint{x2d, y2d, p.p3d[Z]}
		p.p2d = &APoint{x2d, y2d, 0}
	} else {
		p.p2d[X] = x2d;
		p.p2d[Y] = y2d;
		//p.p2d[Z] = p.p3d[Z];
	}
	p.projected = true;
}

// Render the shape (array of pixels)
func (renderer *Renderer) Render(shape []*Pixel) {
	for i:= 0; i < len(shape); i++ {
		pixel := shape[i];
		if (!pixel.projected) {
			renderer.project(pixel);
		}
		w := pixel.p2d;
		if (w[X] < 0 || w[X]  > renderer.width) || (w[Y] < 0 || w[Y] > renderer.height) { continue; }
		wP :=  int(w[X] + w[Y]*renderer.width);
		zp := renderer.zP[wP];
		if zp == nil || zp.p2d[Z] <= pixel.p3d[Z] {
			renderer.zP[wP] = pixel;
		}
	}
}

// Rotate apply rotation through 3 angles
// rX rotation around absolute x axis
// rY rotation around absolute y axis
// rZ rotation around absolute z axis
func (renderer *Renderer) Rotate(shape []*Pixel, rX,rY,rZ float64) []*Pixel {
	mr := NewRot([3]float64{rX, rY, rZ});
	for i:=0 ; i < len(shape); i++ {
		shape[i].p3d = mr.Transform(shape[i].p3d).(*APoint);
		shape[i].projected = false;
	}
	return shape;
}


type Screen struct {
	Buffer string;
}

func NewScreen() *Screen { s:= &Screen{Buffer: ""}; return s; }

func (screen *Screen) spotXY(x, y int, s string, color *AColor) {
	var r,g,b byte;
	r=127;g=127;b=127;
	if (color != nil) {
		r = color[R]; g = color[G]; b = color[B];
	}
	screen.Buffer += fmt.Sprintf("\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%s\x1b[0m", y, x, r, g, b, s);
}

func (screen *Screen) Clear() {
	screen.Buffer = "\x1b[2J";
}

var screen *Screen = NewScreen();

func (renderer *Renderer) Draw() {
	screen.Clear();
	for i:= 0; i < len(renderer.zP); i++ {
		if renderer.zP[i] != nil  && renderer.zP[i].projected {
			x := int(math.Trunc(renderer.zP[i].p2d[X]));
			y := int(math.Trunc(renderer.zP[i].p2d[Y]));
			screen.spotXY(x, y, "\x1b[1mX", renderer.zP[i].color);
			renderer.zP[i] = nil;
		}
	}
	fmt.Print(screen.Buffer);
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

