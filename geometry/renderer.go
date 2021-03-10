package geometry

type Renderer struct {
	halfWidth float64
	halfHeight float64
	width, height int
	zP []AColor  // Zdepth pointers
}

type point2d struct {
	x,y,z float64;
}

func NewRenderer(width, height int) *Renderer {
	r := &Renderer{width: width, height: height};
	r.zP = make([]AColor, width*height);
	r.halfWidth = float64(width)/2;
	r.halfHeight = float64(height)/2;
	return r;
}

func (renderer *Renderer) project(p *APoint, camera  *APoint) *point2d {
	k := camera[Z]/(p[Z] + camera[Z]);
	p2d := &point2d{
		(renderer.halfWidth + ((p[X] - camera[X])*k + camera[X])),
		(renderer.halfHeight - ((p[Y] - camera[Y])*k + camera[Y])),
		p[Z],
	}
	return p2d;
}

