// matou.c yujue

inherit ROOM;

mapping *sign=({
/*    ([  "name":"北京",
        "id":"bj",
        "file":__FILE__,
        "value":10000,
	"time":20
    ]),*/
    ([  "name":"苏州",
        "id":"sz",
        "file":__DIR__"szyunhe",
        "value":500,
	"time":10
    ]),
});

string look_sign();
int do_go(string);

void create()
{
    set("short", "码头");
    set("long",@LONG
这里是古老的运河的桥头边，只见这条运河蜿蜒流淌，从扬州城里穿过。
运河的两岸都是扬州的寻常百姓家，在扬州的城里出门最好的交通工具就是
船了。只见进处有一位老船夫，见你走过来，起身向你迎来，地上立着一个
价格表(sign)。
LONG);
    set("exits", ([
     "north" : "/d/city/dongmen",
    ]));
    set("item_desc", ([
        "sign" : (: look_sign :)
    ]));
    set("outdoor", "city");

    set("coor/x",130);
  set("coor/y",-20);
   set("coor/z",0);
   setup();
}

void init()
{
//    add_action("do_go", "qu");
}

string look_sign()
{
    string str="";
    int i=sizeof(sign);

    while (i--) {
        str += sign[i]["name"];
        str += "(" + sign[i]["id"] + ") ";
        str += MONEY_D->price_str(sign[i]["value"]) + "\n";
    }

    return str;
}

void do_move(object ob, int i)
{
    ob->enable_player();
    ob->delete_temp("block_msg/all");
    write("终点站到了。\n");
    ob->move(sign[i]["file"]);
    tell_room(environment(ob), ob->name() + "从船上走了下来。\n", ({ob}));
}

int do_go(string arg)
{
    object ob=this_player();
    int i=sizeof(sign);

    if (!arg) return 0;
    if (ob->is_busy() || ob->is_fighting())
        return notify_fail("你正忙着呢！\n");
    while(i--) {
        if (arg == sign[i]["id"]) {
            switch (MONEY_D->player_pay(ob, sign[i]["value"])) {
                case 0:
                    return notify_fail("穷光蛋，一边呆着去！\n");
                case 2:
                    return notify_fail("有零钱吗？\n");
            }
	    message_vision("$N登上了去" + sign[i]["name"] + "的船。\n", ob);
	    ob->disable_player("<旅途中>");
	    ob->set_temp("block_msg/all", 1);
	    ob->move(__DIR__"onroad");
            call_out("do_move", sign[i]["time"], ob, i);
            return 1;
        }
    }
    return notify_fail("你要去哪里？\n");
}
