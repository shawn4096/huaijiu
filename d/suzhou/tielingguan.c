inherit ROOM;

void create()
{
        set("short", "�����");
        set("long",@long
�سʳ����Σ�שʯ�ṹ�����е������¥Ϊ�½�������صش�ˮ½Ҫ��
�ǵ�¥���ȿ����������ܷ�����������ԫ���˺ӡ�ʯ������ɵ����Ϲ��£�
��ʱ��Ϊ�˷����ϵֿ����ŵ����ܡ�
long);
set("outdoors", "suzhou");
set("objects",([
__DIR__"npc/wujiang" : 1,
__DIR__"npc/bing" : 3,
]));
set("exits",([
"south" : __DIR__"fengqiao",
]));
set("coor/x",60);
  set("coor/y",-190);
   set("coor/z",-10);
   setup();
}
