// Room: /u/xdd/gumu/fanchuan.c
// Modify By River 98/08
inherit ROOM;
#include <ansi.h>
void create()
{
     set("short",HIY"樊川"NOR);
     set("long", @LONG
此处便是樊川，已是终南山的所在，汉初开国大将军樊哙曾食邑于此，因
而得名。沿途冈峦回绕，松柏森映,水田蔬圃连绵其间，宛然有江南景色。
LONG        );

     set("outdoors","古墓");

     set("exits", ([
         "east" : "/d/xiangyang/shanxiroad1",
         "west" : __DIR__"xiaolu1",
     ]));

     set("coor/x",0);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}

void init()
{       
        object me;
        int lvl;
        mapping learned;
        me = this_player();
        lvl = me->query_skill("xiaohun-zhang", 1);
        learned = me->query_learned();
        me->delete_skill("xiaohun-zhang");
        if (lvl > 0){
                me->delete_skill("anran-zhang");
                me->set_skill("anran-zhang", lvl);
                if (mapp(learned) && learned["xiaohun-zhang"] > 0)
                        me->improve_skill("anran-zhang",
                                learned["xiaohun-zhang"], 1);
                write(HIG "系统已将您的「销魂掌」转换为「黯然销魂掌」。\n" NOR);
         }
        if(me->query_skill_mapped("strike") == "xiaohun-zhang")
            me->map_skill("strike", "anran-zhang");
        if(me->query_skill_mapped("parry") == "xiaohun-zhang")
            me->map_skill("parry", "anran-zhang");
        if(me->query_skill_prepared("strike") == "xiaohun-zhang")
            me->prepare_skill("strike","anran-zhang");
}
