// Room: /d/dali/dg1.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "���¥");
	set("long", @LONG
���¥��������Ҫ�ķ羰��֮һ��λ�ڳ����϶�����ĵ�ذ��ߡ������
�ƣ�Լ�ɷֳ���Ƭ�������֡����¥Ƭ��¥��¥��³԰Ƭ����԰�����Լ���԰
Ƭ�����������ɿ����ܶ�ɻ���
LONG
	);
        set("outdoors", "����");

	set("exits", ([
             "northwest" : __DIR__"xgf",
             "southup" : __DIR__"hg1",
             "south" : __DIR__"tulin",
	     "west" : __DIR__"dg2",
	]));

	set("coor/x",-300);
  set("coor/y",-500);
   set("coor/z",-10);
   set("coor/x",-300);
  set("coor/y",-500);
   set("coor/z",-10);
   setup();
}
