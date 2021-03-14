package registry

// registry is a package to manage a map of entries containing handlers
// each handler is a function
// each entry has a name that should equals the key of the register for entry
// each entry also provides with a summary to describe the entry

type Entry struct {
	Name string
	Summary string
	Handler func()
}

type Register map[string]*Entry;

func NewRegister() Register{ return make(Register); }

func (register Register) AddEntry(entry *Entry) { register[entry.Name] = entry; }

