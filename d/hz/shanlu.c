 // /u/beyond/hz/shanlu.c ɽ·
 
inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long", @LONG
������ɽ·�ϣ���Զ�����ܿ��������������߽���ɫ�����ɽ�ţ�����
����������ŵ�ʯ�����У������ڶ����ţ�������һ�����¶����Ļ�ɫ��ǽ��
ǽ������������š��������������������к�¹�񴰣�������ľ԰������
�䣬��ʾ��԰�ַ�����������׷�����������Ǳ���ɽ��
LONG
        );
set("objects",([
__DIR__"npc/tiao-fu" : 2,
]));
    set("outdoors", "����");
        set("exits", ([
        "eastup" : __DIR__"leifengta",
"north" : __DIR__"shanlu1",
        "southup" : __DIR__"baoshuta",
        "northup" : __DIR__"huanglongdong",
]));
        set("coor/x",60);
  set("coor/y",-300);
   set("coor/z",-10);
   setup();
}
