// Room: /d/dali/futiao.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "����Ͽ");
	set("long", @LONG
��ɳ������������ʯ��֮���д�������ѩɽ�͹���ѩɽ���γɼ�Ϊ׳��
�Ĵ�Ͽ�ȣ�����������Ļ���Ͽ������Ͽȫ��ʮ�幫��Թȵ׵�����ɽ����
�߲����ǧ���ף��������������Ͽ��֮һ�������絶���������ȵ���խ����
������ʮ�ס���˵�о޻�һԾ���������������
LONG
	);
        set("outdoors", "����");

	set("exits", ([
           "east" : __DIR__"nj",
           "northwest" : __DIR__"qunshan",
           "southwest" : __DIR__"ninglang",
	]));

	set("coor/x",-370);
  set("coor/y",-430);
   set("coor/z",-10);
   setup();
}
