// wu-santong.c ÎäÈıÍ¨
// by shang 97/6

inherit NPC;

void create()
{
        set_name("ÎäĞŞÎÄ", ({ "wu xiuwen", "wu" }) );
	set("gender", "ÄĞĞÔ" );
        set("age", 11);
	set("long",
"ÎäÈıÍ¨µÄĞ¡¶ù×Ó¡ \n" "ÎäÑ§Ãû¼ÒµÄ¶ù×Ó£¬È´È¡ÁË¸öË¹ÎÄÃû×Ö¡£\n");
	set("attitude", "friendly");
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 22);
        set("shen_type", 1);

        set_skill("unarmed", 35);
        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set("jiali", 10);

        set("combat_exp", 4000);

        set("max_qi", 250);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("max_jingli", 100);

        set("inquiry", ([
            "ÎäÈıÄï" : "ÊÇÎÒÄï¡£",
            "Îä¶ØÈå" : "ËûÊÇÎÒ¸ç¸ç¡£",
            "ÎäÈıÍ¨" : "ÄãÔõÃ´¿ÉÒÔÔÚ¶ù×ÓÃæÇ°ÌáÀÏ×ÓµÄÃû×Ö? ",
            "here" : "ÎÒÃÔÁËÂ·, Ò²²»ÖªµÀÔÚÄÄÀï¡£",
       ]) );
	setup();
        carry_object("/d/city/obj/cloth")->wear();
}
