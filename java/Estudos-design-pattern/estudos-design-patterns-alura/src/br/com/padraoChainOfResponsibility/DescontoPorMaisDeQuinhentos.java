package br.com.padraoChainOfResponsibility;

public class DescontoPorMaisDeQuinhentos implements Desconto {

	private Desconto proximo;

	public double desconta(Orcamento orcamento) {
		// mais de 5 itens deve haver desconto
		if (orcamento.getItens().size() > 500) {
			return orcamento.getValor() * 0.7;
		}
		return 0;
	}
	
	@Override
	public void setProximo(Desconto desconto) {
		this.proximo = desconto;
	}

}