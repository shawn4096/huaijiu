// Room: xiuxishi2.c

inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
这是间整洁的厢房，因门窗常闭着，光线很昏暗。靠墙点着一炉
檀香，房里别无他物，只有中间放着一张收拾得舒舒服服的大床，床
上还有一些毛毯，看着就让人想睡觉。唯一特别之处是在床边还有一
梳妆小柜，那是给女孩们睡醒后梳妆打扮有的。
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
            return notify_fail("你要找什么\n");
        if (query("tan_count") > 0) 
          {
           message_vision("$N在床上翻来翻去找出一条毛毯。\n", me);
           add("tan_count", -1);
           tan=new(__DIR__"obj/maotan");
           tan->move(me);
          }
        else
           message_vision("$N在床上翻来翻去什么也没找着。\n", me);
     return 1;
}
