// Room: /d/gumu/shulin2.c
#include <ansi.h>
inherit ROOM;
void create()
{
     set("short", GRN"��ľ��"NOR);
     set("long", @LONG
�ò������߳��˴����֣�����������һƬ��ľ���У��������أ��߳��
��������ٲ�ά�衣��ãȻ�Ĺˣ���ϡһ��С·�������С�
LONG);
     set("exits", ([
         "east" : __DIR__"shengou",
         "west" : __DIR__"sl4",
     ]));    
     setup();
}

void init()
{
     	object me = this_player();       
       	if(me->query_skill("hamagong", 1) > 64 &&
           me->query_skill("hamagong", 1) < 115 &&
           me->query("age") >= 17 && 
           me->query("oyf_son") && 
           me->query("oyf_hamagong") < 2 &&
           me->query("combat_exp") > 40000)
           	call_out("do_wait", 30, me);
}

void do_wait(object me)
{
	if( !me ) return;
	if( environment(me) != this_object() ) return;
        write("\n��ͻȻ�������з���֮���������ڲݵ��Ϸ��������\n");
        me->set_temp("oyf_wait", 1);
        call_out("do_idle", 180, me);
}

void do_idle(object me)
{   
	if( !me ) return;
	if( environment(me) != this_object() 
	|| !me->query_temp("oyf_wait") ) return;
	   
       	if(random((int)me->query("kar")) > 22 && (int)me->query_con() > 24){
          	write("\nͻȻ���������ú������죬������������ͬѰ���������ȥ�����������භ��ȭ���Ʒ硣\n");
          	write("������һ����������������Ϥ֮����\n");
          	message_vision(GRN"\n$N�͵������������������䣬�Ѵܽ����������\n"NOR,me);                 
          	me->delete_temp("oyf_wait");
          	me->move(__DIR__"shulin");
        }
       	else{
          	write("����Ȼ���𽭺�������Ī�⣬�常�ֲ�֪��ȥ�����һ���˸�ӿ����ͷ��\n");
          	me->delete_temp("oyf_wait");
          	message_vision(CYN"$N�����̾�˿�����\n"NOR,me);
       }                      
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("oyf_wait"))
                me->delete_temp("oyf_wait");     
        return ::valid_leave(me);
}
