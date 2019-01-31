// caidi.c Modify By River
#include <ansi.h>
inherit ROOM;

int do_chu(string arg);

void create()
{
        set("short",HIG"�˵�"NOR);
        set("long", @LONG
������һ������Ĳ�԰���������Ͳˣ��ܲ������ӣ�˿��֮�ࡣ��Χ����
�ʶ����ˣ�����Ҫ�����ˡ����ڳ��ڵò������õ��չˣ��˵����Ӳݴ�������
�Ĳ˶����Ʋ��ã�����ģ��ض����ˡ�
LONG
        );
        
        set("exits", ([
                "south" : __DIR__"houyuan",
        ]) );

        set("no_fight",1);
   
        set("objects", ([
                __DIR__"npc/guanjia5" : 1,
        ]));

        setup();

}

void init()
{
        add_action("do_chu", "chu");
        add_action("do_chu", "��");        
}

int do_chu(string arg)
{       
        object me,weapon;
        int costj, costq;
        me = this_player();
        if(me->query_temp("job_name")!="����") 
             return notify_fail("���������������⹤�������������! \n");
        if(me->is_busy())
             return notify_fail("��������æ����!\n");
        if(me->is_fighting())
             return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");
        weapon = me->query_temp("weapon");
        if( !weapon || weapon->query("id") != "chu tou")
             return notify_fail("������ʲô�����ݣ�������\n");
        if( !arg || arg != "��" )
             return notify_fail("��Ҫ��ʲô��\n");

        costj = random((int)me->query("con")/3);
        costq = random((int)me->query("str")/3);

        if((int)me->query("jingli") < costj 
         ||(int)me->query("qi") < costq){
          message_vision(HIR"$N��һ�ɣ���С�ĳ����Լ��Ľ��ϡ�\n"NOR,me);
          me->unconcious();
          return 1;
        }        
        me->receive_damage("jingli", costj);
        me->add("qi", -costq);
        if(((int)me->query_temp("mark/��") > 15 + random(5))
         &&(present("caiyuan guanshi", environment(me)))){
          me->set_temp("mark/����",1);
          write(RED "�˵ع���˵���ɵĲ������ˣ�����Ե���ʦ��³������ȥ����(task ok)�ˣ�\n"NOR);
          return 1;
        }  
        write("������ͷ�����ŵ��ϵ��Ӳݳ���������\n");
        me->start_busy(1);
        me->add_temp("mark/��",1);
        if((int)me->query_skill("staff", 1) < 20
         && random(10)>6 ){
          write(HIM"���ڳ����ж����ȵ��÷���Щ���!\n"NOR);
          me->improve_skill("staff", (int)(me->query("int") / 10));
        }
        return 1;
}
