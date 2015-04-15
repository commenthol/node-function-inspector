#include <node.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void fi_inspect(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if(args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return;
	}

	if(!args[0]->IsFunction()) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Argument must be a function")));
		return;
	}

	Local<Function> func = Local<Function>::Cast(args[0]);

	Local<Object> retval = Object::New(isolate);

    Handle<Value> resourceName = func->GetScriptOrigin().ResourceName();
    if (*resourceName) {
        retval->Set(String::NewFromUtf8(isolate, "File"), func->GetScriptOrigin().ResourceName());
    } else {
        retval->Set(String::NewFromUtf8(isolate, "File"), Undefined(isolate));
    }

    retval->Set(String::NewFromUtf8(isolate, "Name"), func->GetName());
    retval->Set(String::NewFromUtf8(isolate, "InferredName"), func->GetInferredName());
    retval->Set(String::NewFromUtf8(isolate, "LineNumber"), Integer::New(isolate, func->GetScriptLineNumber()));
    retval->Set(String::NewFromUtf8(isolate, "ColumnNumber"), Integer::New(isolate, func->GetScriptColumnNumber()));
    
	args.GetReturnValue().Set(retval);
}

void init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "inspect", fi_inspect);
}

NODE_MODULE(addon, init)