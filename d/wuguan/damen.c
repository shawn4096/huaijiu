// Room: damen.c

inherit ROOM;

void create()
{
	set("short", "��ݴ���");
	set("long", @LONG
���ߵ�һ����լ��Ժ���ſڣ����Ž��գ��ſ�վ�ż����Ҷ���һ�������ص��ǣ�
һ��Ҫ�����鷳�����ӡ���ǰ����������ʯʨ�ӣ����弶��ʯ̨���������ȶ���ͭ
���Ĵ��š����ó������ǵ��ش����ס����
LONG);
	set("objects", ([
		"/d/xiangyang/npc/jiading":2,
	]));
	
	set("exits", ([
		"south": "/d/xiangyang/shide",
		"north": "/d/xiangyang/xiaoxiang1",
	]) );
	set("outdoors","���");
	setup();
}
