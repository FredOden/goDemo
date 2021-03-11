package geometry

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
	r.zP = make([]*Pixel, width*height);
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
	p.p2d = &APoint{
		(renderer.halfWidth + ((p.p3d[X] - camera[X])*k + camera[X])),
		(renderer.halfHeight - ((p.p3d[Y] - camera[Y])*k + camera[Y])),
		p.p3d[Z],
	}
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



