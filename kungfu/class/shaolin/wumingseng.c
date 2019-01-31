// Npc: wuming-laoseng
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask();
int ask2(object me);
int ask_fofa();
int ask_reset_skill();
void create()
{
	set_name("������ɮ", ({
                "wuming laoseng",
                "wuming",
                "laoseng",
        }));
        set("long",
                "����һλ�����۵Ŀ���ɮ�ˣ���Ĳ��ߡ�\n"
                "���������Ѯ���⣬ϡϡ����ļ���������Ȼȫ�ס�\n"
        );


        set("nickname", "������ɮ");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");
        set("no_bark",1);

        set("age", 70);
        set("shen", 32000);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 8000);
        set("max_jing", 7000);
        set("eff_jingli", 4000);
        set("neili", 17000);
        set("max_neili", 17000);
        set("jiali", 100);
        set("combat_exp", 3200000);

        set_skill("force", 200);
    	set_skill("yijin-jing", 200);
        set_skill("dodge", 300);
    	set_skill("shaolin-shenfa", 300);
	set_skill("fumoquan-zhen",200);
    	set_skill("claw", 300);
        set_skill("parry", 300);
        set_skill("cuff", 300);
        set_skill("club", 300);
        set_skill("blade", 300);
        set_skill("ranmu-daofa", 300);
        set_skill("finger", 300);
        set_skill("strike", 300);
	set_skill("buddhism", 200);
	set_skill("riyue-bian",300);
	set_skill("whip",300);
        set_skill("yizhi-chan",300);
        set_skill("literate", 100);
set_skill("jingang-quan",300);
set_skill("hand",300);
set_skill("leg",300);
set_skill("ruying-suixingtui",300);
set_skill("banruo-zhang",300);
set_skill("qianye-shou",300);
set_skill("longzhua-gong",300);
set_skill("weituo-chu",300);
set_skill("zui-gun",300);
set_skill("club",300);
map_skill("blade","ranmu-daofa");
map_skill("club","weituo-chu");

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "yizhi-chan");
map_skill("cuff","jingang-quan");
map_skill("leg","ruying-suixingtui");
map_skill("hand","qianye-shou");
map_skill("claw","longzhua-gong");
map_skill("whip","riyue-bian");
map_skill("strike","banruo-zhang");
        prepare_skill("finger", "yizhi-chan");
	set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "jingang" :),
                (: perform_action, "finger.qiankun" :),
                (: perform_action, "finger.wofo" :),
	}));
        create_family("������", 34, "����");         
    set("inquiry", ([
//  "������ҵ":   (: ask :),
"��": (: ask_fofa :),
"����":"��ɮ����ʩ�������ྴ��Ψ��Ӣ���ܱ�ɫ����ʩ����֮������",
"����ʮ����":"����ʮ���ƣ���Ȼ���µ�һ��",
        "������ҵ": (: ask_reset_skill :),
]));

        setup();
	set_temp("apply/damage", 50);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 60);
       	UPDATE_D->get_cloth(this_object());
}

void kill_ob(object me)
{
	command("yun jingang");
        ::kill_ob(me);
}

void attempt_apprentice(object ob)
{
           string new_name;
           if (!ob->query_temp("laoseng_pass",)){
           command("say �Բ����������ڲ���ͽ��");
           return;
         }
        command("recruit " + ob->query("id"));
        new_name=ob->query("name");
        new_name[0..1] = "��";
        ob->set("name", new_name);
	command("say �ӽ��Ժ���ķ�������" + new_name + "�����������������ַ𷨰ɣ�\n");
}

int accept_object(object who, object ob)
{       
         mapping my_fam  = who->query("family");
        if ((string)ob->query("id") != "fanwen jing"){
              command(":)");
            return 0;
           }

       if (!(my_fam) || my_fam["family_name"] !="������"
            || my_fam["generation"] != 36 || who->query_skill("yijin-jing",1) <180
       || who->query_skill("buddhism",1) <160 || who->query_skill("literate",1)<150 || !who->query_temp("sl_bookget"))
      {
           command(":)");
           command("say "+RANK_D->query_respect(who)+"��������Ѿ����͸������֣����Ĵ����ɽ���л����\n");
          command("say �ռ��ǻã��ü��ǿա�\n");
          who->delete_temp("sl_bookget");
          call_out("destroying", 1, ob);
          return 1;
            }
       command("say "+RANK_D->query_respect(who)+"��������Ѿ����һأ���ȴ������Ը�����գ����ա�\n");
       command("look "+(string)who->query("id"));
       command("say "+RANK_D->query_respect(who)+"��Ը������Ϊʦ��\n");
       who->delete_temp("sl_bookget");
       who->set_temp("laoseng_pass",1);
       call_out("destroying", 1, ob);
       return 1;
}
void destroying(object obj)
{
        destruct(obj);
        return;
}

int ask_reset_skill()
{
    object me = this_player();
    if (me->query_skill("riyue-bian", 1) ||
        me->query_skill("weituo-chu", 1) ||
        me->query_skill("ranmu-daofa", 1)) {
          command("say ��Ҫ������ҵ���Ѿ��޳ɵ��书��Ӧ���ȷ������ǡ�");
          return 1;
    }
      if (me->query("passdu")) {
          command("nod");
          command("say �һ�����ȥ��������˵��������쿪ʼ��ȥ��������ϰ�书�ɡ�");
          message_vision(HIR"$N��Ϊǿ�з�����ԭ����ϰ�������񹦣����ڻ�������������˴�롣\n"NOR, me);
          me->set("max_neili", me->query("max_neili")/2);
          me->delete("passdu");
          me->set("pass_xin", 1);
          return 1;
    }
    if (me->query("pass_xin")) {
          command("nod");
          command("say �һ�����ȥ��������˵��������쿪ʼ�͸�������ѧϰ�ɡ�");
          message_vision(HIR"$N��Ϊǿ�з�����ԭ����ϰ�������񹦣����ڻ�������������˴�롣\n"NOR, me);
          me->set("max_neili", me->query("max_neili")/2);
          me->delete("pass_xin");
          me->set("passdu", 1);
          return 1;
    }
    return 0;
}

#include "wuming.h"
