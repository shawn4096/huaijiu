// Room: /d/huashan/shulin.c
// Date: Look 99/03/25

inherit ROOM;

#include <ansi.h>

string* msg1 = ({
	"忽然",
	"突然",
	"猛地",
	"冷不防",
});
string* msg2 = ({
	"从树林里",
	"从树林深处",
});
string* msg3 = ({
	"窜出",
	"杀出",
});
string* msg4 = ({
	"一把夺下",
	"夺下",
	"一把抢去",
	"抢去",
});
string* msg5 = ({
	"处",
	"方向",
	"处夺路",
	"方向夺路",
});

string* names = ({
	"/d/village/caidi",
	"/d/village/shilu1",
	"/d/village/shilu2",
	"/d/village/shilu3",
	"/d/village/shilu4",
	"/d/village/shilu5",
	"/d/village/shilu6",
	__DIR__"canglong",
	__DIR__"celang1",
	__DIR__"celang2",
	__DIR__"chaoyang",
	__DIR__"husun",
	__DIR__"pubu",
	__DIR__"qianchi",
	__DIR__"qingke",
	__DIR__"shaluo",
	__DIR__"sheshen",
	__DIR__"shulin1",
	__DIR__"shulin2",
	__DIR__"shulin3",
	__DIR__"shulin4",
	__DIR__"yuquan",
	__DIR__"yunu",
	__DIR__"zhenyue",
	__DIR__"shanlu1",
	__DIR__"xiaolu2",
	__DIR__"siguoya",
	__DIR__"baichi",
	__DIR__"laojun",
	__DIR__"houtang",
	__DIR__"celang3",
	__DIR__"celang4",
});

void create()
{
        set("short", "树林");
        set("long",@long
这里是华山村里的一片杨树林，如果你没有好身手，可千万不要在此地久
留，据说这里强盗出没，抢劫、杀人的事情经常发生。
long);
        set("exits",([
        "west" : __DIR__"shulin3",
        "north" : __DIR__"shulin2",
        "east" : __DIR__"shulin1",
    ]));
    set("coor/x",40);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

void init(object me)
{
        object ob, name1, ling;
        string objwhere;
        me = this_player();
        name1 = me->query("id");
        ling = present("ling pai", me);
        if( ! (present("mengmian ren", environment(me)) ) 
        && (int)me->query_temp("hs/jobji", 1)==1 
        && (int)me->query_temp("hs/have", 1)==0
        && ling
        && (int)ling->query_temp("done", 1) < 2
        && !(ling->query_temp("hsjob") != name1 )
        &&  random(10) > 3 )
        {
        ob=new(__DIR__"npc/mmr");
        objwhere = names[random(sizeof(names))];
        ob->set("long", ob->query("long")+ "看来就是刚才抢走"+me->query("name")+"("+capitalize(me->query("id"))+")令牌的人。\n");
        ob->set_name("蒙面人", ({ "mengmian ren", "ren", me->query("id")+"'s mmr" }) );
        ob->move(objwhere);
        ling->move(ob);
        me->set_temp("hs/have", 1);
        ling->set_temp("mmr", name1);
        ob->set_temp("mmr", name1);
        message_vision(HIW "\n" + msg1[random(sizeof(msg1))] +
        	msg2[random(sizeof(msg2))] + 
        	msg3[random(sizeof(msg3))] + "一个蒙面人" +
        	msg4[random(sizeof(msg4))] + 
        	"$N的令牌，向" HIY + objwhere->query("short") + 
        	HIW + msg5[random(sizeof(msg5))] + "逃去。\n" NOR, me);
        }
}
