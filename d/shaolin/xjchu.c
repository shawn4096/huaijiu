#include <ansi.h>
inherit ROOM;

int do_pi(string arg);



void create()
{
    set("short", "����");
    set("long", @LONG
һ�䲻���С�ݣ����а���һ�ڴ���������ð�����ڵ�������һ��
�������������ڡ�����������æ�żӲ�ɿ��ȫ�µ���������ζ�
Ҫ���ࡣһλ����ɮ�����ų��صĴ����ף����ڳ����Ľ�����������
LONG
       );
set("no_fight",1);
       set("exits", ([
          "south"  : __DIR__"zhaitang",
]) );
      // set("no_fight",1);
       //set("outdoors","����");
             set("objects", ([
          "d/shaolin/npc/szseng.c" : 1,
       ]));
       set("coor/x",70);
  set("coor/y",250);
   set("coor/z",110);
   setup();
}
void init()
{
        add_action("do_ao", "ao");
        add_action("do_ao", "��");
}
int do_ao(string arg)
{
        object me;
        int costj, costq,times;
        me = this_player();
        if(me->query_temp("job_name")!="����") 
          return notify_fail("�����ɲ���������ĵط����㻹���߿���! \n");
        if (me->is_busy())
         {write("��������æ����!\n");return 1;}
        if (me->is_fighting())
         {write("������ս����,�޷�ר�ĸɻ�!\n");return 1;}
        if ( !arg || arg != "��" )
            {   
                 message_vision("$NҪ��ʲô��\n",me);
                 return 1;
             }
        costj = random((int)me->query("con")/3);
        costq = random((int)me->query("str")/3);
        times=20+random(10);
        if ((int)me->query("jingli") < costj || (int)me->query("qi") < costq)
       {
        message_vision("$N��һ�ɣ���������\n",me);
        me->unconcious();
        return 1;
        }
        
        me->receive_damage("jingli", costj);
        me->add("qi", -costq);       
        if (((int)me->query_temp("mark/��")>times)&&(present("shizhou", environment(me))))
{me->add("sl_job",1);
me->add("potential",20+random(5))
;
             if(me->query("potential") > me->query("max_pot")) me->set("potential", me->query("max_pot"));
             me->add("combat_exp",(int)(me->query_skill("buddhism",1)/5)+60);
             me->delete_temp("job_name");
             me->delete_temp("mark");
            return notify_fail(RED "�̷�ɮ˵������л�������ҵ�æ�����ǿ��ȥ��!!!\n"NOR);
            }  
        message_vision("$N����һ����˫�Ź�ס�����������ڿ��У��ӹ������������������\n", me);
        me->add_temp("mark/��",1);
        
       if ( (int)me->query_skill("hand", 1) < 20 && random(10)>6 )
                {  write(HIM"���ڻ��������У������Ϲ�����Щ����!\n"NOR);
                   me->improve_skill("hand", (int)(me->query_skill("buddhism",1) / 5));
                   me->improve_skill("finger", (int)(me->query_skill("buddhism",1) / 5));
                  }
          return 1;
}
