// matou.c yujue

inherit ROOM;

mapping *sign=({
/*    ([  "name":"����",
        "id":"bj",
        "file":__FILE__,
        "value":10000,
	"time":20
    ]),*/
    ([  "name":"����",
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
    set("short", "��ͷ");
    set("long",@LONG
�����ǹ��ϵ��˺ӵ���ͷ�ߣ�ֻ�������˺��������ʣ������ݳ��ﴩ����
�˺ӵ������������ݵ�Ѱ�����ռң������ݵĳ��������õĽ�ͨ���߾���
���ˡ�ֻ��������һλ�ϴ��򣬼����߹�������������ӭ������������һ��
�۸��(sign)��
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
    write("�յ�վ���ˡ�\n");
    ob->move(sign[i]["file"]);
    tell_room(environment(ob), ob->name() + "�Ӵ�������������\n", ({ob}));
}

int do_go(string arg)
{
    object ob=this_player();
    int i=sizeof(sign);

    if (!arg) return 0;
    if (ob->is_busy() || ob->is_fighting())
        return notify_fail("����æ���أ�\n");
    while(i--) {
        if (arg == sign[i]["id"]) {
            switch (MONEY_D->player_pay(ob, sign[i]["value"])) {
                case 0:
                    return notify_fail("��⵰��һ�ߴ���ȥ��\n");
                case 2:
                    return notify_fail("����Ǯ��\n");
            }
	    message_vision("$N������ȥ" + sign[i]["name"] + "�Ĵ���\n", ob);
	    ob->disable_player("<��;��>");
	    ob->set_temp("block_msg/all", 1);
	    ob->move(__DIR__"onroad");
            call_out("do_move", sign[i]["time"], ob, i);
            return 1;
        }
    }
    return notify_fail("��Ҫȥ���\n");
}
