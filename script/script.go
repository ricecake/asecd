package script;

import (
	"github.com/idada/v8.go"
);

type JSEngine struct {
	engine *v8.Engine
}

func NewJSEngine() *JSEngine {
	engine := v8.NewEngine()
	//global := engine.NewObjectTemplate()
	return &JSEngine{ engine: engine}
}
