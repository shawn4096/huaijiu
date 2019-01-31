// Room: /d/dzd/pubu.c

#include <ansi.h>
inherit ROOM;
string * name1 = ({ "小犬蠢一狼","麻生太狼","安培小三","梅川裤子"}); 

void create()
{
	set("short","瀑布");
	set("long",@LONG
一条巨大的水帘从山上飞流而下，形成一个瀑布。犹如一串高挂在深山老林中的珍珠
项链，又像一幅素绢挂在悬崖前。那飞溅的水露，在山前飘扬，百米之内白蒙蒙一片，常
年飘忽不散，天晴之日，五彩缤纷，光彩夺目，使人如入浑沌迷蒙仙境。透过水雾，隐隐
可看见一个洞口。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"east" : __DIR__"senlin6",	
		"south" : __DIR__"xiliu3",
		"southwest" : __DIR__"caodi3",
	]));
}

void init()
{
	add_action("do_tiao","tiao");
}

int do_tiao(string arg)
{
	object me = this_player();
        object boss;
        string name = name1[random(sizeof(name1))];

	if(me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");
	if(!arg || arg == "" || arg!="pubu")
		return notify_fail("你想往哪儿跳？\n");

	message_vision(HIC"$N纵身提气，朝着瀑布的方向飞跃而去！\n"NOR, me);
        if ( !me->query_temp("marks/勇闯夺命岛4") ){
          write(HIR"\n你忽然感觉瀑布之下全是坚硬的岩石，心中暗叫一声“不好”。\n"NOR);
          tell_room(environment(me), HIR"\n只听见「砰」的一声，"+me->name()+"犹如稻草一般被瀑布湍急的水流给反弹了出来。\n"NOR, ({ me }));
          me->unconcious();
          return 1;
        }

        me->delete_temp("marks/勇闯夺命岛4");
        me->move(__DIR__"rukou");
        boss = new(__DIR__"npc/boss");
        boss->set_name(name, ({ me->query("id")+"'s boss" }) );
        boss->set_temp("target", getuid(me));
        boss->do_copy(me);
        switch( random(4) ) {
                case 0:  
                        boss->move(__DIR__"shidong1");
                        break;
                case 1:  
                        boss->move(__DIR__"shidong2");
                        break;
                case 2:  
                        boss->move(__DIR__"shidong3");
                        break;
                case 3:  
                        boss->move(__DIR__"shidong4");
                        break;
                default: // others      BUG!!!
                        boss->move(__DIR__"rukou");
        }

        message_vision(HIW"\n$N纵身提气，跃进了瀑布之中，使了个「千斤坠」身法，气沉下盘，稳稳站住。\n"NOR, me);
        return 1;
}
	