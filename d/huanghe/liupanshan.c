// by XiaoYao

#include <room.h>

// by XiaoYao

inherit ROOM;
void create()
{
	set("short", "����ɽ");
	set("long", @LONG
����һ����̫�ߵ�Сɽ��ɽ����ȥ�����������Ʈ�ż��䵭���İ��ơ�һ
Ⱥ���㷢�����¸¡��Ľ�������ͷ�Ϸɹ�������ɽ�³��ǵĲ�ԫ�ϱ���ϡ�ɱ�
��·����һ������֮�Ͽ����״ʡ�����ɽ�������ǳǣ�����ɽ����һ��С��ׯ��
LONG );
	set("exits", ([
		"northdown" : __DIR__"yongdeng",
	]));

	set("outdoors", "�ƺ�");
	setup();
}

