// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "�ӻ���");
        set("long", @LONG
����һ����ª���ӻ��꣬���Ƕ���ȴ����ȫ���ϰ峣����ȥ��ԭ�ɹ�һЩ
��Ʒ����������
LONG
        );

        set("exits", ([
                 "west" : __DIR__"jiedao1",
        ]));
        set("objects",([
                __DIR__"npc/laoban" : 1,

        ]));

    
//        set("outdoors", "miaojiang");

        setup();

}
