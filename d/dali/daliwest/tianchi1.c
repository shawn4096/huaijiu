// Room: /d/dali/tianchi1.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
��أ������𳡺������ζ�ǧ�����ʮһ�ס���ˮ����Χɽ����ˮ��۶�
�ɡ�ˮ����̣��������٣�����ï�ܣ�ҰѼ��Ⱥ��ɽɫ��ӳ��εΪ��ۡ�����
����һС�����������з��㣻�����ж�ľ�ۣ����˿ɷ��ۺ��ϣ���������¹����
����ɽ��ˮɫ��һ�أ�ɽ��ζ��һ����ʵΪ�ѵá��򶫣����������ɽ��������
���ɼ����׽��Ұ������������ϡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
             "northeast" : __DIR__"qunshan",
             "up" : __DIR__"tianchi2",
	]));

	set("coor/x",-390);
  set("coor/y",-430);
   set("coor/z",-10);
   setup();
}
