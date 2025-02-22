// By River@sj 99.5.24
// Modified by darken@SJ for public xtjf quest

#include <ansi.h>
#include <room.h>
#include <wanted.h>

inherit ROOM;

string pubu(object);

void create()
{
        set("short",HIW"瀑布"NOR);
        set("long", @LONG
转过一个山峡，水声震耳欲聋，只见山峰间一条大白龙似的瀑布(pubu)奔
泻而下，冲入一条溪流，奔胜雷鸣，湍急异常，水中挟著树枝石块，转眼便流
得不知去向。四顾水气蒙蒙，蔚为奇观。
LONG
    );

       set("outdoors", "襄阳");

       set("item_desc", ([
             "pubu" : (: pubu :),
       ]));

       set("exits", ([
           "west" : __DIR__"xiaolu3",
       ]));
       setup(); 
}

void init()
{
        object me = this_player();
        if ( me->query("family/family_name") != "古墓派" && me->query("ygpass"))
            me->delete("ygpass");
	if (!is_wanted(me))
		add_action("do_tiao", "tiao");
}

string pubu(object me)
{
     return HIW"\n\t一条白龙相仿的瀑布，水流激荡，让人感觉心惊胆战。\n\n"NOR;
}

int do_tiao(string arg)
{
        object me = this_player();
        if (me->is_busy() || me->is_fighting()) 
             return notify_fail("你正忙着呢！\n");

        if( !arg || arg == "" || arg != "pubu" )
             return notify_fail("你要往哪里跳？\n");

        if (me->query_dex() < 27 )
             return notify_fail("你试图跳进瀑布中，但隆隆的水声使你腿有点发软。\n");

        if (me->query_skill("dodge", 1) < 100)
             return notify_fail("你试图跳进瀑布中，却发现自己目前的轻功难以实现。\n");

        if (me->query_skill("force", 1) < 110)
             return notify_fail("你试图跳进瀑布中，却发现自己内功修为似乎还欠缺火候。\n");

        message_vision(HIC"$N纵身提气，朝着瀑布的方向飞跃而去！\n"NOR, me);
        if ( !me->query("ygpass") || me->query("neili") < 2000 ){
          write(HIR"\n你忽然感觉水势甚急，自己无法运气和水流相抗，被激流挤压的左摇右幌。\n"NOR);
          tell_room(environment(me), HIR"\n只听见「砰」的一声，"+me->name()+"犹如稻草一般被瀑布湍急的水流给反弹了出来。\n"NOR, ({ me }));
          me->unconcious();
          return 1;
        }
        me->move(__DIR__"pubu1");
        message_vision(HIW"\n$N纵身提气，跃进了瀑布之中，使了个「千斤坠」身法，气沉下盘，稳稳站住。\n"NOR, me);
        return 1;
}
