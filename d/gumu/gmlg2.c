// Room: /u/xdd/gumu/gmlg2.c
// Modify By River 98/08/29
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
     set("short", HIR"练功房"NOR);
     set("long", @LONG
一间石室，形状甚是奇特，前（frontwall)窄后(backwall)宽，成为梯形，
东(eastwall)边半圆，西(westwall)边却作三角型。室顶石板上刻满诸般花纹
符号，均是已利器刻成，或深或浅，殊无规则。此处供古墓弟子修炼入门外功。
LONG
        );

     set("exits", ([
         "south" : __DIR__"gmzt",          
     ]));

     setup();
}

void init()
{
         add_action("do_xiulian", "xiulian");
         add_action("do_yanxi", "yanxi");
         add_action("do_tui","tui");
}

int do_yanxi(string arg)
{
          mapping fam;
          object me = this_player();
          if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
               return notify_fail("你不是古墓传人，如何能领悟古墓武功？\n");
          if (me->is_busy() || me->is_fighting())
               return notify_fail("你正忙着哪！\n");
          if ((int)me->query_skill("literate", 1) < 30)
               return notify_fail("你丫斗字不识,领悟个啥? \n");            
          if (arg == "top"){
            if (me->query("gender") != "男性")
                return notify_fail("全真剑法呈阳刚之气，只适合男子练习。\n");
            if ((int)me->query_skill("sword", 1) < 20)
                return notify_fail("你基本剑法太差，无法研习全真剑法。\n"); 
            if (me->query_skill("quanzhen-jianfa", 1) >= 1)
                return notify_fail("你已经学会全真剑法，自己好好练吧。\n");      
            write("你仰视室顶的图纹，心中揣摩全真剑法的精妙之处。\n");
            me->receive_damage("jing", 5);
            me->receive_damage("jingli",15);
            me->improve_skill("quanzhen-jianfa", 2);
            return 1;
          }
          return 0;
}

int do_xiulian(string arg)
{
          mapping fam;
          object me = this_player();
          if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
               return notify_fail("你不是古墓传人，如何能领悟古墓武功？\n");
          if (me->is_busy() || me->is_fighting())
               return notify_fail("你正忙着哪！\n");          
          if (me->query("jing") < 20)
               return notify_fail("你精力不能集中,去稍作歇息吧. \n");
          if ((int)me->query_skill("literate", 1) < 30)
               return notify_fail("你丫斗字不识,领悟个啥? \n");
          if (arg == "frontwall"){
            write("你抡掌劈向前方窄窄的石壁，蓬一声被震退数步，手臂一阵酸麻。\n");
            if (me->query_skill("strike", 1) > 50)
               return notify_fail("你掌力雄浑，不该再死练蛮力了。\n");
            me->receive_damage("jing", 5 + random(15));
            me->improve_skill("strike", (int)(me->query_int()/3)+(int)(me->query_skill("strike")/4));
            return 1;
          }
          if (arg == "backwall"){
            write("你挥拳直击弧型后壁，石粉四溅,你也被自己的猛劲震退数步。\n");
            if (me->query_skill("cuff", 1) > 50)
               return notify_fail("你拳力已刚猛无比，却无甚招数。\n");
            me->receive_damage("jing",5 + random(15));
            me->improve_skill("cuff", (int)(me->query_int()/3)+(int)(me->query_skill("cuff",1)/ 4));
            return 1;
          }
          if (arg == "eastwall"){
            write("你绕东面石壁踏着剑步，用心揣摩壁上剑法精髓。\n");
            if (me->query_skill("sword", 1) > 50)
               return notify_fail("你对石壁上所述剑法已全然掌握,无须再费力了. \n");
            me->receive_damage("jing", 5 + random(15));
            me->improve_skill("sword", (int)(me->query_int()/3)+(int)(me->query_skill("sword", 1)/4) );
            return 1;
          }
          if (arg == "westwall"){
            write("你虚拈手指,对着西面的三角形石壁,细心操练暗器的收发手势. \n");
            if (me->query_skill("throwing", 1) > 50 )
               return notify_fail("你暗器收发随心,再不能提高于此. \n");
            me->receive_damage("jing", 5 + random(15));
            me->improve_skill("throwing", (int)(me->query_int()/3)+(int)(me->query_skill("throwing", 1)/4 ));
            return 1;
          }
          return 0;
}

int do_tui(string arg)
{
          mapping fam; 
          object me=this_player();
          if (me->is_busy() || me->is_fighting())
               return notify_fail("你正忙着哪！\n");
          if ( arg == "eastwall"){  
            if (!(fam = me->query("family")) || fam["family_name"] != "古墓派")
               return notify_fail("你不是古墓传人，不能进入古墓密室！\n");
            message_vision(YEL"$N伸手到半圆的弧底推了几下，一块大石缓缓移开，现出一扇洞门。\n"NOR,me);
            set("exits/enter", __DIR__"gmlg3");            
            me->receive_damage("qi", 30); 
            remove_call_out("close");
            call_out("close", 5, this_object());    
            return 1;
          }
          return notify_fail("你要推什么？\n");
}

void close(object room)
{
        message("vision",HIY"大石慢慢退回了原位，又挡住了入口。\n"NOR, room);
        room->delete("exits/enter");
}
