//shuifang.c
// Modify By River@SJ

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIY"ˮ��"NOR);
        set("long", @LONG
һ���ݣ��㿴�����ڷ��ż��ڴ�ף�gang����������װˮ�õģ���������
�����ǿյġ�һȺ��ݵĵ�������æµ������ˮ��ˮ��������һ��ߺ���ţ���
�����˲�Ҫ͵����
LONG
        );
        
	set("item_desc",([
               "gang" :"һ��ˮ�ף�������յ�����һ��ˮҲû�С�\n",
	]));

        set("exits", ([
               "west" : __DIR__"shilu2",               
        ]));

        set("no_fight",1);
        
        set("objects", ([
            __DIR__"npc/guanjia4" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_tiao", "tiao");
        add_action("do_tiao", "��");       
}

int do_tiao(string arg)
{
        object me,weapon;
        int costj, costq;
        me = this_player();
        if(me->query_temp("job_name") != "��ˮ") 
            return notify_fail("���������������⹤�������������! \n");
        if (me->is_busy())
            return notify_fail("��������æ����!\n");
        if (me->is_fighting())
            return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");
        weapon = me->query_temp("weapon");
        if( !weapon || weapon->query("id") != "shui tong")         
            return notify_fail("������ʲô����ˮ��������\n");
        if ( !arg || arg != "ˮ" )
            return notify_fail("��Ҫ��ʲô��\n");
        costj = random((int)me->query("con")/3);
        costq = random((int)me->query("str")/3);
        if((int)me->query("jingli") < costj 
         ||(int)me->query("qi") < costq){
          message_vision(HIR"$N��һ������С��ˮͰ�����Լ����ϡ�\n"NOR,me);
          me->unconcious();
          return 1;
        }        
        me->receive_damage("jingli", costj);
        me->add("qi", -costq);
        if(((int)me->query_temp("mark/��") > 15 + random(5))
         &&(present("shuifang guanshi", environment(me)))){
           me->set_temp("mark/����", 1);
           write(RED"ˮ������˵���ɵĲ������ˣ�����Ե���ʦ��³������ȥ����(task ok)�ˣ�\n"NOR);
           return 1;
        }
        write("��������ˮͰ�е�ˮ������Ȼ����ˮ���С�\n");
        me->start_busy(1);
        me->add_temp("mark/��", 1);
        if((int)me->query_skill("parry", 1) < 20 
         && random(10)>6 ){
          write(HIM"������ˮ�ж����мܵ��÷���Щ���!\n"NOR);
          me->improve_skill("parry", (int)(me->query("int") / 10));
        }
        return 1;
}
