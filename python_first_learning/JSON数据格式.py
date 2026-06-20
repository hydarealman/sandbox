import json
data = [{"name":"张大三","age":11},{"name":"王大锤","age":13},{"name":"赵小虎","age":16}]
json_str = json.dumps(data,ensure_ascii=False)
print(type(json_str))
print(json_str)

s = ' [{"name": "张大三", "age": 11}, {"name": "王大锤", "age": 13}, {"name": "赵小虎", "age": 16}] '
l = json.loads(s)
print(type(l))
print(l)

s = '{"name":"张大三","age":11}'
d = json.loads(s)
print(type(d))
print(d) 