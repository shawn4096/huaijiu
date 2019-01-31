// caiyuan.c Modify By River
#include <ansi.h>
inherit ROOM;

int do_jiao(string arg);

void create()
{
        set("short",HIG"��԰"NOR);
        set("long", @LONG
������һ������Ĳ�԰���������Ͳˣ��ܲ������ӣ�˿��֮�ࡣ��Χ����
�ʶ����ˣ�����Ҫ�����ˡ���԰���м��ڴ�ף�����ʢ����ˮ�����ǲ˵ؿ���
���������ˣ����ò�����ĳ��ţ���ȱˮ̫���ˡ�
LONG
        );
 
        set("exits", ([
                "west" : __DIR__"houyuan",
        ]) );

        set("no_fight",1);

        set("objects", ([
               __DIR__"npc/guanjia6" : 1,
        ]));

        setup();

}

void init()
{
        add_action("do_jiao", "jiao");
        add_action("do_jiao", "��");        
}

int do_jiao(string arg)
{
        object me,weapon;
        int costj, costq;
        me = this_player();
        if(me->query_temp("job_name")!="��Ȳ˵�") 
            return notify_fail("���������������⹤�������������! \n");
        if (me->is_busy())
            return notify_fail("��������æ����!\n");
        if (me->is_fighting())
            return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");
        weapon = me->query_temp("weapon");
        if( !weapon || weapon->query("id") != "piao")
            return notify_fail("������ʲô��Ҩˮ����������\n");
        if ( !arg || arg != "ˮ" )
            return notify_fail("��Ҫ��ʲô��\n");
             
        costj = random((int)me->query("con")/3);
        costq = random((int)me->query("str")/3);

        if((int)me->query("jingli") < costj
         ||(int)me->query("qi") < costq){
          message_vision(HIR"$N�����������Ҩˮ�����ʧ���Ե����\n"NOR,me);
          me->unconcious();
          return 1;
        }
        me->receive_damage("jingli", costj);
        me->add("qi", -costq);       
        if(((int)me->query_temp("mark/��") > 15 + random(5))
         &&(present("caiyuan guanshi", environment(me)))){
          me->set_temp("mark/����",1);
          write(RED "��԰����˵���ɵĲ������ˣ�����Ե���ʦ��³������ȥ����(task ok)�ˣ�\n"NOR);
          return 1;
        }  
        write("����ư�Ӹ���Ҩ��ˮ���ڲ˵��ｽ��ˮ���� \n");
        me->start_busy(1);
        me->add_temp("mark/��",1);
        if((int)me->query_skill("force", 1) < 20
         && random(10)>6 ){
          write(HIM"���ڽ�ˮ�ж����ڹ����÷���Щ���!\n"NOR);
          me->improve_skill("force", (int)(me->query("int") / 10));
        }
        return 1;
}
