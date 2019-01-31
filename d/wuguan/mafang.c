// mafang.c Modify By River
inherit ROOM;
#include <ansi.h>

int do_sao(string arg);

void create()
{
        set("short",HIG"���"NOR);
        set("long", @LONG
������ݵ���ǣ���������ģ����˼�ʮƥ������ǰ���ǣ�������
���տ���������ι�����㣬��ϴˢ�ø�Ǭ����������жѷ������Ѳ��ϣ�����
��һ����ۣ�������Щ��ˮ��
LONG
        );
        
        set("exits", ([
               "north" : __DIR__"shilu2",
        ]));

        set("no_fight",1);

        set("objects", ([
                __DIR__"npc/guanjia3" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_sao", "clean");
        add_action("do_sao", "sao");        
}

int do_sao(string arg)
{    
        object me,weapon;
        int costj, costq;
        me = this_player();
        if(me->query_temp("job_name")!="��ɨ��") 
             return notify_fail("���������������⹤�������������! \n");
        if (me->is_busy())
             return notify_fail("��������æ����!\n");
        if (me->is_fighting())
             return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");
        weapon = me->query_temp("weapon");
        if( !weapon || weapon->query("id") != "sao zhou")
             return notify_fail("������ʲô����ɨ������ɨ��\n");
        if ( !arg || arg != "��" )
           return notify_fail("��Ҫ��ɨʲô��\n");
             
        costj = random((int)me->query("con")/3);
        costq = random((int)me->query("str")/3);

        if((int)me->query("jingli") < costj 
         ||(int)me->query("qi") < costq){
          message_vision(HIR"$N��һ������С�Ļ���������\n"NOR,me);
          me->unconcious();
          return 1;
        }        
        me->receive_damage("jingli", costj);
        me->add("qi", -costq);       
        if(((int)me->query_temp("mark/ɨ") > 15 + random(5))
         && (present("mafang guanshi", environment(me)))){
          me->set_temp("mark/����",1);
          write(RED "������˵���ɵĲ������ˣ�����Ե���ʦ��³������ȥ����(task ok)��!!!\n"NOR);
          return 1;
        }  
        write ("�����˸��ط���ʼɨ���������湻���ģ��㲻�ɱս��˺�����\n");
        me->start_busy(1);
        me->add_temp("mark/ɨ",1);
        if((int)me->query_skill("club", 1) < 20
         && random(10) > 6 ){
          write(HIM"����ɨ���ж��ڹ����÷���Щ���!\n"NOR);
          me->improve_skill("club", (int)(me->query("int") / 10));
        }
        return 1;
}
