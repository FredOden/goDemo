package screen

// Screen is a basic screen interface with essential methods
type Screen interface {
	SpotXY(x,y int, color *AColor)
	SetText(x,y int, color *AColor, text string)
	Clear()
	Flush()
}
