// /d/wudang/gudao3.c  古道

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"古道"NOR);
        set("long", @LONG
你走走停停，发现已到了路的尽头。这里凌空突出，长满青草，几只野兔
在你身边跳来跳去毫不怕生，下面十多丈深有一水潭，潭水清澈。你
正满身臭汗饥渴难当，恨不得马上跳下去凉快一番。
LONG                           
        );
        set("exits", ([
                "southup" : __DIR__"gudao2",

        ]));

        set("objects",([        
                __DIR__"npc/yetu" : 2,
                __DIR__"obj/lxshi":1,
        ]));

        setup();

}
void init()
{
    add_action("do_jump","tiao");
}

int do_jump(string arg)
{       object me,tmp;
        me=this_player();
        if ( !arg || arg != "down" )
            return notify_fail("你要往哪跳?\n");
        message_vision(HIY"$N一招狗急跳墙，四肢平展猛得朝水潭跳下。\n"NOR, me);
        me->move(__DIR__"shuitan");
        message_vision(RED"    扑通一声，$N肚子首先入水，五脏六腑一阵翻滚。张嘴想要惊呼，
咕噜咕噜，反而被灌了一肚子水。\n"NOR, me);
        me->receive_damage("jingli", 20);
        me->set("water", me->max_water_capacity()+200);
        if ((int)me->query_dex()<33 && (tmp=present("lianxin shi",me)) )
        {
         message_vision(HIW"$N不堪重负，身体象秤砣般下沉。\n"NOR, me);
         me->move(__DIR__"tandi1");
         me->apply_condition("diving",1);
         write("你连忙丢掉沉重物品。\n");
         tmp->move(environment(me));
         me->start_busy(2);
         destruct(tmp);
         message_vision(HIY"$N扔掉的东西都咕噜咕噜地沉向潭底去了。\n"NOR,me);
       }
    return 1;
}

