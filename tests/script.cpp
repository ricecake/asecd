#include <v8.h>
#include <string>
#include <iostream>

using namespace v8;


Handle<Context> CreateContext(Isolate* isolate);
int main(int argc, char* argv[]) {
  // Create a new Isolate and make it the current one.

	V8::Initialize();

  Isolate* isolate = Isolate::New();
  Isolate::Scope isolate_scope(isolate);

  // Create a stack-allocated handle scope.
  HandleScope handle_scope(isolate);

  // Create a new context.
  Local<Context> context = CreateContext(isolate);

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope(context);

  // Create a string containing the JavaScript source code.
  Local<String> source = String::NewFromUtf8(isolate, "dumpObject({hello: 'world'}); 'Hello' + world()");

  // Compile the source code.
  Local<Script> script = Script::Compile(source);

  // Run the script to get the result.
  Local<Value> result = script->Run();

  // Convert the result to an UTF8 string and print it.
  String::Utf8Value utf8(result);
  printf("%s\n", *utf8);
  return 0;
}



void dumpObject(const FunctionCallbackInfo<Value>& args) {
	auto isolate = args.GetIsolate();
	HandleScope handle_scope(isolate);
	auto context = isolate->GetCurrentContext();
	auto global  = context->Global();
    	auto JSON    = global->Get(String::NewFromUtf8(isolate, "JSON"))->ToObject();
	auto JSON_stringify = Handle<Function>::Cast(JSON->Get(String::NewFromUtf8(isolate, "stringify")));

	Handle<Value> FuncArgs[] = { args[0] };

	std::string  string = *String::Utf8Value(JSON_stringify->Call(JSON, 1, FuncArgs));

	std::cout<< string <<std::endl;

	printf("JSON:\n%s\n", *String::Utf8Value(JSON_stringify->Call(JSON, 1, FuncArgs)));

	return;
}

void World(const FunctionCallbackInfo<Value>& args) {
	args.GetReturnValue().Set(Handle<String>(String::NewFromUtf8(args.GetIsolate(), "WORLD!!!")));
	return;
}

// Creates a new execution environment containing the built-in
// functions.
Handle<Context> CreateContext(Isolate* isolate) {
  // Create a template for the global object.
  Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);

  global->Set(String::NewFromUtf8(isolate, "world"), FunctionTemplate::New(isolate, World));
  global->Set(String::NewFromUtf8(isolate, "dumpObject"), FunctionTemplate::New(isolate, dumpObject));

  // Bind the global 'print' fiunction to the C++ Print callback.
//  global->Set(v8::String::NewFromUtf8(isolate, "print"),
//              v8::FunctionTemplate::New(isolate, Print));
  // Bind the global 'read' function to the C++ Read callback.
//  global->Set(v8::String::NewFromUtf8(isolate, "read"),
//              v8::FunctionTemplate::New(isolate, Read));
  // Bind the global 'load' function to the C++ Load callback.
//  global->Set(v8::String::NewFromUtf8(isolate, "load"),
//              v8::FunctionTemplate::New(isolate, Load));
  // Bind the 'quit' function
//  global->Set(v8::String::NewFromUtf8(isolate, "quit"),
//              v8::FunctionTemplate::New(isolate, Quit));
  // Bind the 'version' function
//  global->Set(v8::String::NewFromUtf8(isolate, "version"),
//              v8::FunctionTemplate::New(isolate, Version));


  
  return v8::Context::New(isolate, NULL, global);
}


/*
void Read(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 1) {
    args.GetIsolate()->ThrowException(
        v8::String::NewFromUtf8(args.GetIsolate(), "Bad parameters"));
    return;
  }
  v8::String::Utf8Value file(args[0]);
  if (*file == NULL) {
    args.GetIsolate()->ThrowException(
        v8::String::NewFromUtf8(args.GetIsolate(), "Error loading file"));
    return;
  }
  v8::Handle<v8::String> source = ReadFile(args.GetIsolate(), *file);
  if (source.IsEmpty()) {
    args.GetIsolate()->ThrowException(
        v8::String::NewFromUtf8(args.GetIsolate(), "Error loading file"));
    return;
  }
  args.GetReturnValue().Set(source);
}
*/
