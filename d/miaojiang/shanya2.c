// /u/dubei/miaojiang
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
�������嶾���Աߵ�һ��С�յأ�һ����Χǽ��һ���Ƕ��͵�ʯ�ڡ�ʯ��
�ǳ��⻪�������Ӻ�������ȥ��
LONG
        );

        set("exits", ([
                
                "west" : __DIR__"wddamen",
                
        ]));
 
        set("outdoors", "miaojiang");

        setup();
}
/*
void init()
{
        add_action("do_pa", ({ "climb", "pa" }));
} 

int do_pa(string arg)
{
       object me;
       me = this_player(); 
        if (arg != "shanya" ) return 0;
         if ( !arg ) return 0;

        if (!living(me)) return 0;
        if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 20) {
		message_vision("$N��������ණ������������ȥ��\n", me);
		me->unconcious();
		return 1;
	} 
          if( (int)me->query_skill("dodge",1) < 100 ) {  
 
        message_vision(HIR"$N��Ҫ����ɽ���������Ṧ������ˤ��������\n"NOR, me);
        me->unconcious();
        return 1;     
        }  
        message_vision("$N΢΢����������Խ����ȥ��\n", me);
       me->move(__DIR__"guanmucong1");
       tell_room(environment(me), me->name() + "����������������\n", ({ me }));
      
     	return 1;
}
*/
