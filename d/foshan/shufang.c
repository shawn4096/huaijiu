// Room: /d/fuoshan/shufang.c 
 
inherit ROOM; 
#include <wanted.h>

void create() 
{ 
	set("short", "�鷿");
	set("long", @LONG
�����Ƿ����ϵ��鷿��ȴû��һ���顣���ֹ���������Ŀ��������ͭ
�������ʣ����鱦ʯ��Ӧ�о��У���ͨ��ֻҪӵ��һ�����͹�һ�Ҵ�С��
��һ�����ˡ������ǽ�Ϲ���һ����(picture)��
LONG
	);

        set("exits", ([
              "north" : __DIR__"dating",
]));
        set("item_desc", ([
                "picture" :      
        "����һ�������ɽˮ����������ⱦ��֮���Ե��ر����ۡ�\n",
]));

	set("coor/x",30);
  set("coor/y",-560);
   set("coor/z",0);
   setup();
}


void init()
{
     add_action("do_use","use");
        add_action("do_touch", "touch");
}

int do_touch()
{
        write("����û���Щ�������̲�סȥ�������о����ı�����Щ��͹��ƽ�����ƿ�
����������һ��С�ף������ܲ���Կ�ס�\n");
	this_player()->set_temp("marks/okay",1);
	return 1;
}

int do_use(string arg)
{
	object me = this_player();
	if (is_wanted(me)) return 0;
	if( !me->query_temp("marks/okay")  ) return 0;
	if( !me->query_temp("marks/zhong") ) return 0;
    	if( !arg || arg=="" ) return 0;
        if (!present("hei yaoshi", me))  return 0;
        if(arg=="hei yaoshi")
	{
	write("ͻȻ��֨��֨���죬�ذ嶯������������һ��������һ��ͨ���Ķ�������
æ������ȥ\n");      
    me->move("/d/foshan/mishi");
	me->delete_temp("marks/zhong");
	me->delete_temp("marks/okay");
	return 1;
	}
	else return 0;
}


