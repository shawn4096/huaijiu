// Room: /d/dali/qunshan.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "÷��ѩɽ");
	set("long", @LONG
����߷������������ѩ�����������ִ���ɽ������ٲȻ��һ����ѩ���硣
����֮�������ֻ�ѩ�ڻ�����ˮк���£��������գ�εΪ��ۡ������վ�����
�Ⱥܶ������������ֱ�߾���Ϊʮ�����������С����͵ĸ�ɽ�ݹȵ��Σ�
�Ǻ����ľ��ۡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
             "southeast" : __DIR__"futiao",
             "southwest" : __DIR__"tianchi1",
	]));

	set("coor/x",-380);
  set("coor/y",-420);
   set("coor/z",-10);
   setup();
}
