package geometry


type Point struct {
	x,y,z float64;
};

func (p *Point) Create(x,y,z float64) {
	p.x = x;
	p.y = y;
	p.z = z;
}

func (p *Point) Copy(from *Point) {
	p.x = from.x;
	p.y = from.z;
	p.z = from.z;
}

func (p *Point) SetX(x float64) { p.x = x;}; func(p *Point) GetX() float64 { return p.x };
func (p *Point) SetY(y float64) { p.y = y;}; func(p *Point) GetY() float64 { return p.y };
func (p *Point) SetZ(z float64) { p.z = z;}; func(p *Point) GetZ() float64 { return p.z };

func (from *Point) To(to *Point) *Vector { var v Vector; v.Create(to.x - from.x, to.y - from.y, to.z - from.z); return &v;};

func (p *Point) Translate(v *Vector) *Point { var t Point; t.Copy(p); t.x += v.u; t.y += v.v; t.z +=v.w; return &t; }

