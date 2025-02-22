// Room: /city/pomiao.c
// update by Looklove at 2000/8/25

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "土地庙");
      set("long", @LONG
这是一间破破烂烂的土地庙，庙里破败不堪，土地神像推在一旁，梁上地
下也布满了灰尘。一看就知道已经很久没有人来清理过了。正中放着个大香案，
上面零乱地扔着几根吃剩下来的鸡骨头。也许正是因为隐蔽的原因吧，据说丐
帮江南据点就被设在此处。北面墙上开着一个小门。
LONG
        );

      set("valid_startroom", 1);

      set("exits", ([
                "south" : __DIR__"xinglin9",
                "north" : __DIR__"houyuan",
      ]));

      set("objects", ([
                CLASS_D("gaibang") + "/lu" : 1,
      ]));
      setup();
        create_door("north", "竹门", "south", DOOR_CLOSED);
}

void reset()
{
     object ob=present("lu youjiao",this_object());
     ::reset();
     if(ob){
       ob->delete_temp("gb_job2");
       ob->delete_temp("gb_job3");
       ob->delete_temp("gb_job4");
     }
}

void init()
{       
        object me = this_player();
        int lvl,lvl1,lvl2;
        lvl = me->query_skill("bangjue", 1);
        lvl1 = me->query_skill("huntian-qigong", 1);
        if (lvl > 200 && !me->query("cut/gb")){
                lvl2 = (lvl - 200)/ 4;
                me->set_skill("bangjue", 200);
                me->set_skill("huntian-qigong", lvl1 + lvl2);
                me->set("cut/gb", lvl2 * 4);
                write(HIG "系统已将您多余的「打狗棒诀」转换为「混天气功」。\n" NOR);
        }
}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");
        if ((!myfam || myfam["family_name"] != "丐帮") &&
            objectp(present("lu youjiao", environment(me))) && dir == "north")
           return notify_fail("鲁有脚抱拳道：没事不要打扰帮主。\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 30 &&
            objectp(present("lu youjiao", environment(me))) && dir == "north")
           return notify_fail("鲁有脚说道：没事别打扰帮主。\n"); 

        return ::valid_leave(me, dir);
}

