// gsz.c ����ֹ
// By River 99.5.25
#include <ansi.h>
inherit NPC;
string ask_gu();
void create()
{
	set_name("����ֹ", ({ "gongsun zhi", "gongsun", "zhi" }));
	set("long","��ĿӢ����͸�������߾�֮�ţ�ֻ����ɫ���ƣ����տ��¡�\n");
        set("title",HIW"����ȹ���"NOR);
	set("gender", "����");
	set("age", 45);
	set("attitude", "friendly");
	set("shen", -3000);
	set("str", 25);
	set("int", 24);
	set("con", 28);
	set("dex", 26);
        set("per", 20);
        set("unique", 1);

	set("max_qi", 2500);
	set("max_jing", 2000);
	set("neili", 3000);
	set("max_neili", 3000);
        set("eff_jingli", 2000);
	set("jiali", 80);
	set("combat_exp", 1000000);
 
        set_skill("force", 150);      
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("guiyuan-tunafa", 150);
        set_skill("literate", 120); 
        set_skill("shuishangpiao", 150);
        set_skill("tiezhang-zhangfa", 150);
        set_skill("strike",150);
        set_skill("sword", 150);
	set_skill("liangyi-jian", 150);

        map_skill("force", "guiyuan-tunafa");
        map_skill("dodge", "shuishangpiao");
        map_skill("strike", "tiezhang-zhangfa");
        map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
        prepare_skill("strike", "tiezhang-zhangfa");

        set("inquiry", ([
            "���鵤": "��ҩ�޶࣬����Ҳ�������ƣ����򲻵��ѡ�����",
            "�����": (: ask_gu :),
        ]) );

	setup();
	carry_object("/clone/weapon/sword")->wield();
	carry_object("/clone/armor/cloth")->wear();
}

string ask_gu()
{
       object me,ob;
       me=this_object();
       ob=this_player();
       if(ob->query("combat_exp") < 200000)
         return RANK_D->query_respect(ob)+"����̫�������������ΪΣ�գ����ǲ�Ҫ�ڴ˾����ˡ�";      
         ob->set_temp("gsz_agree", 1);
         return RANK_D->query_respect(ob)+"��Ȼ�Ծ����������Ȥ��������㿴���ɡ�";
}
