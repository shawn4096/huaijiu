// Room: xiuxishi2.c

inherit ROOM;

void create()
{
        set("short", "��Ϣ��");
        set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵����ǽ����һ¯
̴�㣬����������ֻ���м����һ����ʰ����������Ĵ󴲣���
�ϻ���һЩë̺�����ž�������˯����Ψһ�ر�֮�����ڴ��߻���һ
��ױС�����Ǹ�Ů����˯�Ѻ���ױ����еġ�
LONG
        );
        set("tan_count", 2);

        set("sleep_room", 1);
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"donglang2",

        ]));

        set("coor/x",-10);
  set("coor/y",-70);
   set("coor/z",100);
   setup();
}

void init()
{
        add_action("do_zhao", "find");
        add_action("do_zhao", "zhao");

}

int do_zhao(string arg)
{       object tan;
        object me;
        me=this_player();
        if ( !arg || arg != "mao tan" )
            return notify_fail("��Ҫ��ʲô\n");
        if (query("tan_count") > 0) 
          {
           message_vision("$N�ڴ��Ϸ�����ȥ�ҳ�һ��ë̺��\n", me);
           add("tan_count", -1);
           tan=new(__DIR__"obj/maotan");
           tan->move(me);
          }
        else
           message_vision("$N�ڴ��Ϸ�����ȥʲôҲû���š�\n", me);
     return 1;
}
