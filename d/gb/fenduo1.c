// fenduo1.c ؤ����ŷֶ�
// Modify by Looklove@SJ at 2000/9/26

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","���ŷֶ�");
	set("long", @LONG
�����ؤ��Ĵ��ŷֶ棬��������ݵ����񡣲����ܵĴ����ص����ϵģ���
��ֻ����һյ�͵ƣ�����ϡ��������������ǣ�����ζ��ùζ����һ�飬�������
�����ˡ���������Χ�˼�����ؤ���ƺ�����������ʲô��һ�����Ǳ��ϵĲ�����֪
�������ǰ�����е�λ�����
LONG
	);
	set("exits",([
	"out" : __DIR__"yuchuan5",
	]));
	set("objects", ([
                CLASS_D("gaibang") + "/jiang" : 1,
                CLASS_D("gaibang") + "/wu" : 1,
	]));

	set("valid_startroom",1);
	set("coor/x",120);
  set("coor/y",-470);
   set("coor/z",20);
   setup();
       call_other("/clone/board/gb_board", "???");
}

