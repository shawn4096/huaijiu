// fenduo2.c ���ݷ�ĹĹ��(gb���·ֶ�)
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","Ĺ��");
	set("long", @LONG
����һ���ܴ��Ĺ�ң��������Ų����ˡ�ǽ�Ϲ����˻�棬�յù�
�����ġ�ԭ�������ؤ��Ĵ��·ֶ棬һȺ��ؤΧ�ŵ�ͼ���ƺ����ڼ�
�ҵ�������ʲô��ǽ�Ǵ�����һ�ڿݾ�(well)��
LONG
	);
	set("valid_startroom",1);
	set("item_desc",([
	"well" : "��������ɵģ���֪ͨ�����\n",
	]));
            set("exits", ([
                      "north" : __DIR__"mushizl",                
          ]));
	set("objects",([
                CLASS_D("gaibang") + "/xi" : 1,
//		__DIR__"npc/fangqiu" : 1,
                __DIR__"npc/jydizi" : 1,
	]));
	set("coor/x",110);
  set("coor/y",60);
   set("coor/z",-10);
   setup();
          call_other("/clone/board/gb_board2", "???");
}

void init()
{
        object me = this_player();
        if ( me->query("title") == "ؤ����·ֶ��������")
        {
                me->set("title","ؤ����·ֶ�һ������");
        }
	add_action("do_jump","jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if( arg=="well" )
        {
		if (me->is_busy())
			return notify_fail("����æ���ء�\n");
                message("vision",
                        me->name() + 
	 	        "���������һ������һ���ۣ�������������ȥ��\n",
                        environment(me), ({me}) );
                me->move("/d/gb/shangang");
                message("vision",
                        me->name() + "�ӷ�Ĺ��ð�˳�����\n",
                        environment(me), ({me}) );
                return 1;
        }
}

