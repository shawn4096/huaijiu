
#include <ansi.h>
inherit ROOM;

void run_mufa(object me);
void run_mufa1(object me);
void run_mufa2(object me);
void run_mufa3(object me);


void create()
{
        set("short", "�촬");
        set("long", @LONG
��������¹�����һ�ҿ촬��
���ڳ����࣬��Ʒ������룬���������Ĵ����ڴ��ϴ��ָ���£���������ز���
�Ŵ�ֻ��
LONG
);
        set("no_fight",1);
        set_temp("curstatus","ready");
        setup();
}

void init()
{
        object me = this_player();

        if(!me->query_temp("marks/�´�������2",1)) {
        	message_vision("ͻȻ�и��˷���һ�Ű�$N���˳�ȥ��\n",me);
        	me->move(__DIR__"dukou");
        	tell_object(environment(me),me->name()+"���˴ӿ촬������������\n",({me}));
        	return;
       	}  
        if(userp(me)) {
                call_out("run_mufa", 2,me);
        }
}

void run_mufa(object me)
{        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision(HIC"\n\n$N�����ϴ�����������ȥ���ۼ�������ӿ���Ƶ����գ���ֻ��Ÿ���Ӳ����衣\n"NOR,me);
        call_out("run_mufa1", 1+random(1), me);
}

void run_mufa1(object me)
{        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision(CYN"\n\n�˿̺����������촬������ʻ��Ƭ�̹����$N���ں��涫����������һ��½�ء�\n"NOR,me);
        call_out("run_mufa2", 1+random(1), me);
}

void run_mufa2(object me)
{        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision(WHT"\n\nת�ۼ�촬��Ȼʻ��½�أ�����������ľ�Դ䣬�����ĺ�̲��������ͷ������ѩ��ϸɳ��\n"NOR, me);
        call_out("run_mufa3", 1+random(1), me);
}

void run_mufa3(object me)
{
        int i;
        i = 1 + random(3);
        if(i>3) i = 3;
        
        if(!me){
        	destruct(this_object());
        	return;
        }
        message_vision("�촬��������ꑵأ�$N�����ػ������ܣ�һ����������ɳ̲֮�ϡ�\n",me);
        me->delete_temp("marks/�´�������2");
        me->move("/cmds/leitai/dmd/haitan1");
        me->set_temp("marks/�´�������3",i);
        tell_room(environment(me), me->name() + "�ӿ촬�������¡�\n",me);  
        destruct(this_object());
}