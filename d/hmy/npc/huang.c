#include <ansi.h>
inherit NPC;
void create()
{
      
	set_name("�Ʋ���", ({ "huang boliu", "huang",}));
	set("nickname", "������");        
        set("long", 
"����ͷ�����ź�ɫͷ�֣�������������ò�Ե�ʮ�ֹ��ء�\n");
        set("title",HIY"�������  "HIC"����������"NOR);
        set("gender", "����");
        
	set("age", 30);
	set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("max_qi", 700);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 600);
        set("jiali", 50);
        set("combat_exp", 100000);
     
        set_skill("parry",100);
        set_skill("dodge",100);
        set_skill("ding-dodge",100);        
        set_skill("force",100);
        set_skill("huntian-qigong",100);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "huntian-qigong");
        
	create_family("�������",3,"����");
        setup();

}

