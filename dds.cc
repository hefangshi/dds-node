#include <unistd.h>
#include <node.h>
#include <v8.h>
#include <uv.h>
#include <dll.h>
#include <string.h>

using namespace v8;
using namespace node;

struct async_req {
  uv_work_t req;
  ddTableDealPBN input;
  ddTableResults output;
  Persistent<Function> callback;
};

void DoAsync (uv_work_t *r) {
  async_req *req = reinterpret_cast<async_req *>(r->data);
  CalcDDtablePBN(req->input,&req->output);
}

void AfterAsync (uv_work_t *r) {
  HandleScope scope;
  async_req *req = reinterpret_cast<async_req *>(r->data);

  Handle<v8::Array> v8Res = v8::Array::New(4);
  for (int i = 0; i < 4; ++i)
  {
        Handle<v8::Array> v8row = v8::Array::New(5);
        for (int j = 0; j < 5; ++j)
        {
            v8row->Set(j, v8::Integer::New(req->output.resTable[i][j]));
        }
        v8Res->Set(i, v8row);
  }

  Handle<Value> argv[1] = { v8Res };

  TryCatch try_catch;

  req->callback->Call(Context::GetCurrent()->Global(), 1, argv);

  // cleanup
  req->callback.Dispose();
  delete req;

  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
}

Handle<Value> NODE_CalcDDtablePBN(const Arguments& args) {
  HandleScope scope;

  async_req *req = new async_req;
  req->req.data = req;

  char *pbn_arg;
  v8::String::Utf8Value input (args[0]->ToString());
  pbn_arg = *input;
  ddTableDealPBN pbn;
  strncpy(pbn.cards, pbn_arg, sizeof pbn.cards - 1);
  pbn.cards[sizeof pbn.cards-1] = '\0';

  req->input = pbn;

  Local<Function> callback = Local<Function>::Cast(args[1]);
  req->callback = Persistent<Function>::New(callback);

  uv_queue_work(uv_default_loop(),
                &req->req,
                DoAsync,
                (uv_after_work_cb)AfterAsync);

  return Undefined();
}

void init(Handle<Object> target) {
        InitStart(0, 0);
        NODE_SET_METHOD(target, "CalcDDtablePBN", NODE_CalcDDtablePBN);
}

NODE_MODULE(dds, init);
