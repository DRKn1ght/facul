/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trabalho;

/**
 *
 * @author Gabriel
 */
public class Prontuario {
    private String sintomas;
    private String diagnosticoDoenca;
    private String prescricaoTratamento;
    
    public String getSintomas(){
        return this.sintomas;
    }
    
    public void setSintomas(String sintomas){
        this.sintomas = sintomas;
    }
    
    public String getDiagnosticoDoenca(){
        return this.diagnosticoDoenca;
    }
    
    public void setDiagnosticoDoenca(String diagnosticoDoenca){
        this.diagnosticoDoenca = diagnosticoDoenca;
    }
    
    public String getPrescricaoTratamento(){
        return this.prescricaoTratamento;
    }
    
    public void setPrescricaoTratamento(String prescricaoTratamento){
        this.prescricaoTratamento = prescricaoTratamento;
    }
}
