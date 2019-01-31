#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", GRN "�Ӱ�" NOR);
        set("long", @LONG
����ˮ��֮�ص����Ӳ��ݺᣬǰ����С����·���޷����С�������һ
Ƭ�����֣��������������������һ��С�ţ������¼�ҶС�ۣ�������
��������Ů������������ת���˵Ľ���С����
LONG); 
        set("no_sleep_room", 1);
        set("exits", ([
              "west" : __DIR__"xiaojing1",
        ]));
        set("objects", ([
               __DIR__"npc/xia" : 1,                             
        ]));  
        set("outdoors", "����");
        set("coor/x",150);
  set("coor/y",-320);
   set("coor/z",0);
   setup(); 
}

void init()
{   
    	object me = this_player();
    	int luck = me->query_temp("oyf/meet");
    
    	me->receive_damage("jingli", 10);
    	if(!me->query("oyf/son") && me->query("oyf/fail") < 4
        && random((int)me->query("kar")) == 2){
           	if(!luck && me->query_condition("bing_poison") > 20 &&          
              		me->query("combat_exp") > 100000000){
              		write("\n��ͻȻ���ú������˸��������ת��ͷ��ȴ����ʲôҲû�С�\n\n");
              		me->set_temp("oyf/meet", 1);
              	}   
           	else if (luck >= 10) {
                	write("\n��������һ��˵������С���ޣ�֪�������˰գ�����������ϴ̶����ƴӵص��������һ�㡣\n");
                	message_vision("\n$NͻȻ����һ������ͷ�㷢��񱼡�\n",me);         
                	me->delete_temp("oyf/meet");
                	me->set_temp("oyf/ok", 1); 
                	call_out("wait", 10, me);         
                }
           	else if (luck >= 1) {
                	write("\n��ͻȻ���ú��������������ת��ͷ��ȴ����ʲôҲû�С�\n\n"); 
                	me->add_temp("oyf/meet", 1); 
                }
        }                             
}

void wait(object me)
{
        int total, try;
        
        if(!me || environment(me) != this_object() || !living(me)) return;
        
        total = me->query("kar")+me->query("per")+me->query("con");
        try = (int)me->query("oyf/fail");
        
        if(random(total) > 850){
              	message_vision(HIR"\n$Nֻ���ֱ���ľ�����Ѳ���ʹ����ֻ���ô����죬��֪����Ǻã��������ܽ����������ӡ�\n\n"NOR,me);
              	me->move(__DIR__"river1");
        }
        
        else {
              	me->add("oyf/fail", 1);    
              	message_vision(HIR"\n$N����ͻȻһ����µµ�ع�������ʮ�ɣ�\n\n"NOR,me);
              	me->delete_temp("oyf/ok");     
              	me->move(__DIR__"shulin1");
              	me->receive_damage("qi", 100);
              	me->receive_wound("qi", 100);
              	tell_room(environment(me), HIR + me->name()+"��µµ�ع��˹��������ڵ��ϰ�������������\n" NOR,({ me }));   
        }
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("oyf/ok") && dir == "west")
                return notify_fail("��������һ���죬һ����Ӱ����ͷ��Ծ������������ǰ��\n");
        return ::valid_leave(me, dir);
}
