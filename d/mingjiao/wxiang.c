// wxiang.c ���᷿
// Modify By River@SJ 99.06
#include <ansi.h>
#include <room.h>
inherit ROOM;
void init();
void create()
{ 
       set("short",HIM"���᷿"NOR);
       set("long", @LONG
��һ����һ�������ﾹ��һ����˼�С��Ĺ뷿�������ߵ���һ������
̨��̨�Ϻ�����գ���ҫ�÷��л��Ž��أ��ûʸ�������һ����һ����������
������(zhang)�ʹ���������һ���̺��
LONG);
	set("exits", ([
		"east" : __DIR__"yuanzi",				
	])); 
	set("item_desc", ([
		"zhang" : "����һ���ʹ������ʣ�����������������˯����\n"
	]));            
	set("objects",([
                CLASS_D("mingjiao") + "/yang1" : 1,
	]));
	set("coor/x",-260);
  set("coor/y",270);
   set("coor/z",120);
   setup();       
}

void init()
{
	add_action("do_xian","xian");
	add_action("do_tang","tang");
}
	
int do_xian(string arg)
{
	object me=this_player();

	if (arg !="zhang" || me->is_busy()) return 0;
	tell_object(me,"���ƿ����ʣ�ͻȻ��������������һ�Ŵ����������̲�ס����(tang)����������˯��һ����\n");
	me->set_temp("marks/��1", 1);
	return 1;
}

int do_tang(string arg)
{
	object me=this_player();

	if (me->is_busy())
		return 0;
	if (me->query_temp("marks/��1")){
	    message("vision", me->name() + "������������ȥ��ͻȻ����һ�࣬"+me->name()+"ˤ����ȥ��\n", environment(me), ({me}));
            me->move(__DIR__"didao/bidao1");
            message("vision", me->name() + "ͻȻ�������ˤ��������\n", environment(me), ({me}) );
            me->delete_temp("marks/��1");
	return 1;
	}
}
