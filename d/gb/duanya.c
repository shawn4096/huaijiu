#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
ǰ����һ��ʮ�ֶ��͵Ķ��£��վ��쳣��������Խ(pa)��
LONG
        );

        set("exits", ([ 
          "north" : "/d/shaolin/yidao4",
]));

        set("coor/x",110);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}
void init()
{
        add_action("do_pa", ({ "climb", "pa" }));
} 

int do_pa(string arg)
{
       object me;
       me = this_player(); 

        if (arg != "ya" && arg!="up") 
          return notify_fail("��Ҫ����������\n");
         if ( !arg ) return 0;

        
        if (!living(me)) return 0;
        if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 30
|| !me->query_temp("gb_job2") )
         {
                message_vision("$N�������꣬�е��޷�����ȥ��ˤ��������\n", me);
		me->receive_wound("qi", 50+random(50));
		me->set_temp("last_damage_from", "�Ӷ����ϵ�����ˤ");
                return 1;
        } 

        if( (int)me->query_skill("dodge",1) < 80 ) 
        {  
		message_vision(HIR"$N��Ҫ����ɽ���������Ṧ������ˤ��������\n"NOR, me);
		me->receive_wound("qi", 50+random(50));
		me->set_temp("last_damage_from", "�Ӷ����ϵ�����ˤ");
		return 1;     
        }  
        message_vision("$N��סͻ������ʯ��ʩչ�Ṧ������ȥ��\n", me);
        me->move(__DIR__"yading");
        tell_room(environment(me), me->name() + "����������������\n", ({ me }));
        return 1;
}
