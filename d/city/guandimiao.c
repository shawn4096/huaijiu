// Room: /d/city/guandimiao.c
// Date: Look 99/09/20

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", HIR "�ص���" NOR);
	set("long", @LONG
�������ݳǶ����һ���ص�����˵ҹ�ﾭ�������ڴ˾������ƣ���ͨ��
���ǲ��������Ƿ�֮�صġ�
�������������Ĺص۵����������������ֳ��������µ������Ҹ��ǹع��Ľ���
�ֵ��������ŷɣ�һ�����������ˣ��·�Ҫɱ�����²���֮�ˡ�
LONG
	);
        set("indoors", "����");

	set("exits", ([
      "southwest" : __DIR__"dongmen",
	]));
//	set("objects", ([__DIR__"npc/linghuchong" : 1]));

	set("coor/x",140);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

void init()
{
	object me = this_player();
  	object weapon = me->query_temp("weapon");
	if (weapon)
	{
	tell_object(me, YEL"�㿴���ص۵���������񣬴��˸���ս�����Խ��ķ��������еı�����\n"NOR);
	weapon->unequip(); 
       // me->start_busy(random(15));
	}
//	add_action("do_jiebai","jiebai");
} 

/*
int do_jiebai(string arg)
{
	string arg1, arg2, arg3;
       	object me, ob1, ob2, ob3;
       	int i;
       	me = this_player();
       	if (!arg) return notify_fail("��ʽ��jiebai with <id> <id> <id>\n");
       	i = sscanf(arg, "%s %s %s", arg1,arg2,arg3);
        if( i >= 0 && i <= 2 )
        {
        	if (arg1){
                if( !(ob1 = present(arg1, environment(me)))
                ||      !living(ob1)
                ||      !ob1->is_character()
                ||      ob1==me )
                        return notify_fail("��Ҫ��˭��ݣ�\n");
                }
                if (arg2){
                if( !(ob2 = present(arg2, environment(me)))
                ||      !living(ob3)
                ||      !ob2->is_character()
                ||      ob2==me
                ||	ob2==ob1 )
                        return notify_fail("��Ҫ��˭��ݣ�\n");
                }
                if (arg3){
                if( !(ob3 = present(arg3, environment(me)))
                ||      !living(ob3)
                ||      !ob3->is_character()
                ||      ob3==me
                ||      ob3==ob2
                ||      ob3==ob1 )
                        return notify_fail("��Ҫ��˭��ݣ�\n");
                }
        }
        else
        {
                return notify_fail("��ݵ����������Ƕ����ĸ���\n");
	}
        return notify_fail("Ŀǰ��"+(string)i+"����ݶ���"+arg1+arg2+arg3+"\n");
}
*/
