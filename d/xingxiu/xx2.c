// Room: /d/xingxiu/xx2.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
这里是星宿海。因方圆几百里都是一望无际的湖泊和沼泽，当地
牧羊人称之为“海”。也因阴暗潮湿，毒虫繁殖甚富。星宿弟子常来
此捕捉毒虫，以备练毒之用。这里通向星宿海的深处。西面有一条小
径，两旁点缀了些花卉。虽是稀少，但在星宿海是一奇观了。不由得
让人心花怒放，哼起了小曲。
LONG
        );
        set("objects", ([                
                __DIR__"npc/chuchen" : 1,
        ]) );

        set("exits", ([
             "southeast" : __DIR__"xx1",
             "west" : __DIR__"xx3",
             "enter" : __DIR__"cangku",
        ]));

        set("outdoors", "xingxiuhai");
        set("yushi_count", 1);
        set("coor/x",-310);
  set("coor/y",180);
   set("coor/z",0);
   setup();
}

void init()
{
   	object me = this_player();
  
   	if( me->query("family/family_name") == "星宿派" && me->query("xx_points") > 10
      	&& (random(30) == me->query("kar")) && query("yushi_count") >= 1 && !me->query_temp("yushi_get")){
      		write("你看见土里有个东西一"WHT"闪"NOR"，拣起来才发现原来是一小块玉石！\n");
      		me->set_temp("yushi_get", 1);
      		new(MISC_D("yushi"))->move(me);
      		add("yushi_count", -1);
      	}
}

int valid_leave(object me, string dir)
{   
        if( me->query("family/family_name") != "星宿派" && dir == "enter")
//        && objectp(present("chuchen zi", environment(me))))
            return notify_fail("里面传出一股非常恶心的气味，你一闻就想吐，进不了这个山洞！\n");
        
        return ::valid_leave(me, dir);
}
