// mufang.c Modify By River
#include <ansi.h>
inherit ROOM;

int do_ju(string arg);

void create()
{
        set("short",HIG"ľ��"NOR);
        set("long", @LONG
�ս��ݣ���ͱ��޴�ľ�ľ����ס�ˣ�������˺ö೤��ľͷ��׼��Ҫ��
����õģ���������ȥ��ǰ�ȵðѳ�ľͷ��̳�һ�ؽصģ������ò�������
���������ڷ����ľ���ľͷ��
LONG
        );
        
        set("exits", ([
              "east" : __DIR__"shilu2",
        ]));

        set("objects", ([
             __DIR__"npc/guanjia2" : 1,
        ]));

        set("no_fight",1);

        setup();
}

void init()
{
        add_action("do_ju", "ju");
        add_action("do_ju", "��");        
}

int do_ju(string arg)
{      
        object me,weapon;
        int costj, costq,i;
        i=0;
        me = this_player();
        if(me->query_temp("job_name")!="��ľͷ") 
            return notify_fail("���������������⹤�������������! \n");
        if (me->is_busy())
            return notify_fail("��������æ����!\n");
        if (me->is_fighting())
            return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");   
        weapon = me->query_temp("weapon");
        if( !weapon || weapon->query("id") != "ju zi")
            return notify_fail("������ʲô����ľͷ����������\n");
        if ( !arg || arg != "ľͷ" )
            return notify_fail ("��Ҫ��ʲô��\n");                 
             
        costj = random((int)me->query("con")/3);
        costq = random((int)me->query("str")/3);

        if ((int)me->query("jingli") < costj 
         || (int)me->query("jing") < costq){
          message_vision(HIR"ľͷ���ˣ�$Nһû�����õ�������ľͷ�����˽��ϡ�\n"NOR,me);
          me->unconcious();
          return 1;
        }        
        me->receive_damage("jingli", costj);
        me->add("qi", -costq);       
        if(((int)me->query_temp("mark/��") > 15 + random(5))
         &&(present("mufang guanshi", environment(me)))){  
          me->set_temp("mark/����",1);
          write(RED "ľ������˵���ɵĲ������ˣ������ȥ��ʦ��³���Ǹ���(task ok)�ˣ�\n"NOR);
          return 1;
        }
        write("�����һ��ľͷ����������������\n");
        me->start_busy(1);
        me->add_temp("mark/��",1);
        if((int)me->query_skill("hand", 1) < 20
         && random(10)>6 ){
          write(HIM"���ھ�ľͷ�������жԻ����ַ���Щ���!\n"NOR);
          me->improve_skill("hand", (int)(me->query("int") / 10));
        }
        return 1;
}
