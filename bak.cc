#include <node.h>
#include <v8.h>
#include <dll.h>
#include <string.h>

using namespace v8;

Handle<Value> NODE_CalcDDtablePBN(const Arguments& args) {
  HandleScope scope;
  char *pbn_arg;
  v8::String::Utf8Value input (args[0]->ToString());
  pbn_arg = *input;
  ddTableDealPBN pbn;
  strncpy(pbn.cards, pbn_arg, sizeof pbn.cards - 1);
  pbn.cards[sizeof pbn.cards-1] = '\0';
  ddTableResults result;

  CalcDDtablePBN(pbn,&result);

  Handle<v8::Array> v8Res = v8::Array::New(4);
  for (int i = 0; i < 4; ++i)
  {
        Handle<v8::Array> v8row = v8::Array::New(5);
        for (int j = 0; j < 5; ++j)
        {
                v8row->Set(j, v8::Integer::New(result.resTable[i][j]));
        }
        v8Res->Set(i, v8row);
  }
  return scope.Close(v8Res);
}

void init(Handle<Object> target) {
  InitStart(0, 0);
  NODE_SET_METHOD(target, "CalcDDtablePBN", NODE_CalcDDtablePBN);
}

NODE_MODULE(dds, init);