//Npc songshan shi.c 史登达
//Modify by baimo 2000,12,11 for a new job

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_job();
string ask_fangqi();

void create()
{
        set_name("史登达", ({ "shi dengda", "shi", "dengda" }));
        set("nickname", "千丈松");
        set("long", "这是左冷禅的徒弟，他是位身材甚高的黄衫汉子。\n");
        set("gender", "男性");
        set("age", 26);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 23);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);
        
        set("max_qi", 1400);
        set("max_jing", 1000);
        set("eff_jingli", 1000); 
        set("jiali", 20);
        set("combat_exp", 700000);
        set("shen", -7000);

    	set_skill("force", 100);
    	set_skill("hanbing-zhenqi", 100);
    	set_skill("dodge", 100);
    	set_skill("zhongyuefeng", 100);
        set_skill("hand", 100);
        set_skill("songyang-shou", 100);
    	set_skill("parry", 100);
    	set_skill("sword", 100);
    	set_skill("songshan-jian", 100);
    	set_skill("literate", 50);
    	map_skill("force", "hanbing-zhenqi");
    	map_skill("dodge", "zhongyuefeng");
        map_skill("hand", "songyang-shou");
    	map_skill("parry", "songshan-jian");
    	map_skill("sword", "songshan-jian");
        prepare_skill("hand", "songyang-shou");
    	create_family("嵩山派", 5, "弟子");
        set("inquiry", ([
                       "job" :( : ask_job :),
                       "工作" :(: ask_job :),
                       "fangqi":(: ask_fangqi :),
                       "放弃" :(: ask_fangqi :),
                ]));
        
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();   
        carry_object(BINGQI_D("changjian"))->wield();         
}

void attempt_apprentice(object ob)
{
     	if(ob->query("shen") < 0 && ob->query("combat_exp") < 10000){
        	command("say 你这邪魔外道，还敢来我嵩山派？快滚！");
        	return;
        }
        if (ob->query("family") && ob->query("family/family_name")!="嵩山派")
        {
                command("say "+RANK_D->query_respect(ob)+"已经是"+ ob->query("family/family_name")+"弟子，在下怎敢再收你为徒？"); 
                return;
        }

     	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
     	command("recruit " + ob->query("id"));
}
int ask_job()
{
	object me;
        me = this_player();
        
        if (me->query("family/family_name")!="嵩山派" ){
                command("say 你不是我嵩山弟子，哪凉快哪歇着去吧！\n");
                command("sneer");
                return 1;
        }
        if (me->query("combat_exp")>=100000){
                command("say 你的功夫已经很高了，再做下去我多没面子。\n");
                return 1;
        }
        if (me->query_temp("ss_qs/asked")){
                command("say 你刚才不是问过了吗，怎么还不去？\n");
                return 1;
	}
        if (me->query_condition("job_busy")){
                command("say 你手头还有其他的事吧？过一会再来吧！\n");
                return 1;
        }
        me->set_temp("ss_qs/asked",1);
        me->apply_condition("job_busy",4);
        message_vision(HIC"史登达说道：掌门召开英雄会需要修整封禅台，$N速去观胜峰帮忙采石。\n"NOR,me);
        return 1;
}
string ask_fangqi()
{
        object me;
        me = this_player();
        
        if(me->query("family/family_name")!="嵩山派")
              return "你非嵩山派弟子,跑这里瞎嚷嚷什麽?";
        if(!me->query_temp("ss_qs/asked"))
              return "什么放弃？放什么弃？";

        me->delete_temp("ss_qs");
        me->clear_condition("job_busy");
        me->start_busy(1);
        me->apply_condition("job_busy",3+random(3));
        return "好吧，那你就歇会先？";
}
