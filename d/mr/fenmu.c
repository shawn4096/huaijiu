#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short",BLU"Ĺ��"NOR);
	set("long", @LONG
������Ľ���ϵķس�, Ľ��������Ҫ����������,��������, 
��һ���⡣ÿ������ʱ��, Ľ�ݺ��ᶼҪ��������档����һ����
�ظ�������סĿ, ��ǰ��һ��Ĺ��(bei),����Ľ�ݸ�֮��Ľ�ݲ�֮Ĺ��
LONG);
	set("exits", ([
		"west" : __DIR__"xiaojing1-4",
	]));

	set("book_count",1);
	setup();
}

void init()
{
	this_player()->set_temp("ketou_times", 30);
	add_action("do_ketou", "ketou");
	add_action("do_push", "push");
}

int do_push(string arg)
{
	if ( !arg || (arg != "bei") )
		return notify_fail("��Ҫ��ʲô��\n");       
	
	if((int)this_player()->query("neili")< 1000)
		return notify_fail("��о������������������ģ�ԭ�������������ˡ�\n");

	message_vision("$N���һ����˫������Ĺ����ֻ��Ĺ��������һ�����ڣ�$N����һԽ������Ӱ��\n",this_player());
	  this_player()->move(__DIR__"mishi");
	message_vision("$N�ӷ�Ĺ���˽����� \n",this_player());

	return 1;
}

int do_ketou()
{
	object me, ob;

	me = this_player();
		
	if ( me->query_temp("ketou_times") == 0 )
	{
		message_vision("$N��ͷ�ĵ����˹�ȥ��\n", me);
		me->set_temp("ketou_times", random(30));
		me->unconcious();
		return 1;
	}

	me->add_temp("ketou_times", -1);	

	message_vision("$N�ϵع���������Ĺ����ǰ��ͷ��\n", me);

	if ( random(100) == 37 
	&& !present("force book", me)
	&& query("book_count") >= 1)
	{
		add("book_count", -1);
 ob=new(__DIR__"obj/neigong-book");
  ob->move(__DIR__"fenmu");
		tell_object(me, "ͻȻ����ǰ��ž��һ������һ���ڹ��ķ���\n");
	}


	if ((int)me->query_skill("force", 1) >= 30 
	&& (int)me->query_skill("force", 1) <= 100 
	&& present("force book", me) )
	{
		me->receive_damage("jing", 20);
		me->improve_skill("force", me->query("int"));
		if ( random(5) == 0 )
tell_object(me, "ڤڤ֮�У����ƺ����ý���������ڹ���������ѡ�\n");
	}

	return 1;

}

int valid_leave(object me, string dir)
{
	if(me->query_temp("ketou_times") >= 0 ) me->delete_temp("ketou_times");

	return ::valid_leave();
}

