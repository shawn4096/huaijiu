// Room: /u/xdd/gumu/gmbedroom.c
// Modify By River 98/08/29
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
          set("short",HIC"��Ϣ��"NOR);
          set("long", @LONG
�����ǹ�Ĺ���ӵ���Ϣ�ң����пտն�����һ���Ĺ���졣һ�鳤����ʯ
���������������Ų�ϯ��һ���ײ������������������һ���˸ߵ����������
�У��������
LONG        );

          set("exits", ([
               "north" : __DIR__"gmht",
          ]));

          set("objects", ([
                __DIR__"obj/bed" : 1,
          ]));

          set("sleep_room", 1);
          set("no_fight", 1);

          create_door("north", "ʯ��", "south", DOOR_CLOSED);
          setup();
}

void init()
{
          add_action("do_zuo", "zuo");
          add_action("do_liao", "liao");
}

int do_zuo(string arg)
{
         mapping fam;
         object me = this_player();
         if (me->is_busy() || me->is_fighting())
               return notify_fail("����æ���ģ�\n");
         if (!(fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
               return notify_fail("�㲻�ǹ�Ĺ���ˣ�����������Ĺ�书��\n");
         if (arg == "bed"){
           if (me->query("jing") < 20 )
              return notify_fail("��ľ�̫�٣��޷������Ϻ���\n");
           if (me->query("potential", 1) < 1)
              return notify_fail("���Ǳ��û�ˣ������ټ�����ϰ��\n");
           write(HIC"�㳤��һ�����������������ȶ�����\n"NOR);
           if (me->query_skill("force", 1) < 10){
               message_vision(HIR"$N��δ����,�͹ֽ�һ��, �Ӵ�������������������ܲ���ǧ�����֮������\n"NOR, me);
               return 1;
           }
           if (me->query_skill("yunu-xinjing", 1) > 50)
                return notify_fail("�����Ů�ľ������൱���,���񴲲�����������ϰ�ڹ��ˡ�\n");
           me->receive_damage("jing", 150 / (int)me->query("int"));
           me->add("potential", -1);
//         me->start_busy(random(2));
           write("���ź���֮��Ȼ��Ч��������Ȼ�������㿪ʼ��ϰ�ڹ��ķ������������ޱȡ� \n"NOR);
           me->improve_skill("yunu-xinjing", me->query_int() + random(me->query_int() * 5 / 6));
           return 1;
         }
         return notify_fail("��Ҫ��������? \n");
}

int do_liao(string arg)
{
         object me = this_player();
         if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ���ء�\n");
         if ((int)this_player()->query("eff_qi")==(int)this_player()->query("max_qi"))
                 return notify_fail("����������û���ܵ��κ��˺���\n");
         if (arg == "bed"){
            message_vision(HIC"$N���Ϻ���, Ҫ��ǧ�꺮������. \n"NOR, me);
            if ((int)me->query_condition("marks_bed") > 0 ){
                 me->receive_wound("qi", 10);
                 message_vision(HIR"$NͻȻֻ��һ���溮�������壬������������ʱ��̫�̣�������δ��ԭ֮�ʡ�\n"NOR, me);
                 me->unconcious();
                 return 1;
            }
            if (me->query_skill("yunu-xinjing", 1) < 40)
              return notify_fail("�����������Դ������Ů�ľ��ڹ��ศ, �����޷�����. \n");
            me->set("eff_qi", me->query("max_qi"));
            tell_object(me,HIW"\n��һ�������ֻ����������ȣ��˿���ȻȬ����\n"NOR);
            me->apply_condition("marks_bed", 25);
            return 1;
         }
         return notify_fail("��Ҫ��������? \n");
}
